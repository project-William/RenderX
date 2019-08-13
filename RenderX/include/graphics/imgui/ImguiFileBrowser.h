#pragma once

#include "..//..//..//Core.h"
#include <filesystem>




namespace renderx {

	namespace ui {

		using ImGuiFileBrowserFlags = int;

		enum ImGuiFileBrowserFlags_
		{
			ImGuiFileBrowserFlags_SelectDirectory = 1 << 0, // select directory instead of regular file
			ImGuiFileBrowserFlags_EnterNewFilename = 1 << 1, // allow user to enter new filename when selecting regular file
			ImGuiFileBrowserFlags_NoModal = 1 << 2, // file browsing window is modal by default. specify this to use a popup window
			ImGuiFileBrowserFlags_NoTitleBar = 1 << 3, // hide window title bar
			ImGuiFileBrowserFlags_NoStatusBar = 1 << 4, // hide status bar at the bottom of browsing window
			ImGuiFileBrowserFlags_CloseOnEsc = 1 << 5, // close file browser when pressing 'ESC'
			ImGuiFileBrowserFlags_CreateNewDir = 1 << 6, // allow user to create new directory
		};

		class REN_API ImguiFileBrowser
		{
		public:

			// pwd is set to current working directory by default
			explicit ImguiFileBrowser(ImGuiFileBrowserFlags flags = 0);

			ImguiFileBrowser(const ImguiFileBrowser& copyFrom);

			ImguiFileBrowser& operator=(const ImguiFileBrowser& copyFrom);

			// set the window title text
			void SetTitle(std::string title);

			// open the browsing window
			void Open();

			// close the browsing window
			void Close();

			// the browsing window is opened or not
			bool IsOpened() const noexcept;

			// display the browsing window if opened
			void Display();

			// returns true when there is a selected filename and the "ok" button was clicked
			bool HasSelected() const noexcept;

			// set current browsing directory
			bool SetPwd(const std::filesystem::path& pwd = std::filesystem::current_path());

			// returns selected filename. make sense only when HasSelected returns true
			std::filesystem::path GetSelected() const;

			// set selected filename to empty
			void ClearSelected();

		private:

			class ScopeGuard
			{
				std::function<void()> func_;

			public:

				template<typename T>
				explicit ScopeGuard(T func) : func_(std::move(func)) { }
				~ScopeGuard() { func_(); }
			};

			void SetPwdUncatched(const std::filesystem::path& pwd);

			ImGuiFileBrowserFlags flags_;

			std::string title_;
			std::string openLabel_;

			bool openFlag_;
			bool closeFlag_;
			bool isOpened_;
			bool ok_;

			std::string statusStr_;

			std::filesystem::path pwd_;
			std::string selectedFilename_;

			struct FileRecord
			{
				bool isDir;
				std::string name;
				std::string showName;
			};
			std::vector<FileRecord> fileRecords_;

			// IMPROVE: overflow when selectedFilename_.length() > inputNameBuf_.size() - 1
			static constexpr size_t INPUT_NAME_BUF_SIZE = 512;
			std::unique_ptr<std::array<char, INPUT_NAME_BUF_SIZE>> inputNameBuf_;

			std::string openNewDirLabel_;
			std::unique_ptr<std::array<char, INPUT_NAME_BUF_SIZE>> newDirNameBuf_;
		};
	} 

	inline renderx::ui::ImguiFileBrowser::ImguiFileBrowser(ImGuiFileBrowserFlags flags)
		: flags_(flags),
		openFlag_(false), closeFlag_(false), isOpened_(false), ok_(false),
		inputNameBuf_(std::make_unique<std::array<char, INPUT_NAME_BUF_SIZE>>())
	{
		if (flags_ & ImGuiFileBrowserFlags_CreateNewDir)
			newDirNameBuf_ = std::make_unique<std::array<char, INPUT_NAME_BUF_SIZE>>();

		inputNameBuf_->at(0) = '\0';
		SetTitle("file browser");
		SetPwd(std::filesystem::current_path());
	}

	inline renderx::ui::ImguiFileBrowser::ImguiFileBrowser(const ImguiFileBrowser& copyFrom)
		: ImguiFileBrowser()
	{
		*this = copyFrom;
	}

	inline renderx::ui::ImguiFileBrowser& renderx::ui::ImguiFileBrowser::operator=(const ImguiFileBrowser& copyFrom)
	{
		flags_ = copyFrom.flags_;
		SetTitle(copyFrom.title_);

		openFlag_ = copyFrom.openFlag_;
		closeFlag_ = copyFrom.closeFlag_;
		isOpened_ = copyFrom.isOpened_;
		ok_ = copyFrom.ok_;

		statusStr_ = "";
		pwd_ = copyFrom.pwd_;
		selectedFilename_ = copyFrom.selectedFilename_;

		fileRecords_ = copyFrom.fileRecords_;

		*inputNameBuf_ = *copyFrom.inputNameBuf_;

		if (flags_ & ImGuiFileBrowserFlags_CreateNewDir)
		{
			newDirNameBuf_ = std::make_unique<std::array<char, INPUT_NAME_BUF_SIZE>>();
			*newDirNameBuf_ = *copyFrom.newDirNameBuf_;
		}

		return *this;
	}

	inline void renderx::ui::ImguiFileBrowser::SetTitle(std::string title)
	{
		title_ = std::move(title);
		openLabel_ = title_ + "##filebrowser_" + std::to_string(reinterpret_cast<size_t>(this));
		openNewDirLabel_ = "new dir##new_dir_" + std::to_string(reinterpret_cast<size_t>(this));
	}

	inline void renderx::ui::ImguiFileBrowser::Open()
	{
		ClearSelected();
		statusStr_ = std::string();
		openFlag_ = true;
		closeFlag_ = false;
	}

	inline void renderx::ui::ImguiFileBrowser::Close()
	{
		ClearSelected();
		statusStr_ = std::string();
		closeFlag_ = true;
		openFlag_ = false;
	}

	inline bool renderx::ui::ImguiFileBrowser::IsOpened() const noexcept
	{
		return isOpened_;
	}

	inline void renderx::ui::ImguiFileBrowser::Display()
	{
		ImGui::PushID(this);
		ScopeGuard exitThis([this] { openFlag_ = false; closeFlag_ = false; ImGui::PopID(); });

		if (openFlag_)
			ImGui::OpenPopup(openLabel_.c_str());
		isOpened_ = false;

		// open the popup window

		if (openFlag_ && (flags_ & ImGuiFileBrowserFlags_NoModal))
			ImGui::SetNextWindowSize(ImVec2(700, 450));
		else
			ImGui::SetNextWindowSize(ImVec2(700, 450), ImGuiCond_FirstUseEver);
		if (flags_ & ImGuiFileBrowserFlags_NoModal)
		{
			if (!ImGui::BeginPopup(openLabel_.c_str()))
				return;
		}
		else if (!ImGui::BeginPopupModal(openLabel_.c_str(), nullptr,
			flags_ & ImGuiFileBrowserFlags_NoTitleBar ? ImGuiWindowFlags_NoTitleBar : 0))
		{
			return;
		}
		isOpened_ = true;
		ScopeGuard endPopup([] { ImGui::EndPopup(); });

		// display elements in pwd

		int secIdx = 0, newPwdLastSecIdx = -1;
		for (auto& sec : pwd_)
		{
#ifdef _WIN32
			if (secIdx == 1)
			{
				++secIdx;
				continue;
			}
#endif
			ImGui::PushID(secIdx);
			if (secIdx > 0)
				ImGui::SameLine();
			if (ImGui::SmallButton(sec.u8string().c_str()))
				newPwdLastSecIdx = secIdx;
			ImGui::PopID();
			++secIdx;
		}

		if (newPwdLastSecIdx >= 0)
		{
			int i = 0;
			std::filesystem::path newPwd;
			for (auto& sec : pwd_)
			{
				if (i++ > newPwdLastSecIdx)
					break;
				newPwd /= sec;
			}
#ifdef _WIN32
			if (newPwdLastSecIdx == 0)
				newPwd /= "\\";
#endif
			SetPwd(newPwd);
		}

		ImGui::SameLine();

		if (ImGui::SmallButton("*"))
			SetPwd(pwd_);

		if (newDirNameBuf_)
		{
			ImGui::SameLine();
			if (ImGui::SmallButton("+"))
			{
				ImGui::OpenPopup(openNewDirLabel_.c_str());
				(*newDirNameBuf_)[0] = '\0';
			}

			if (ImGui::BeginPopup(openNewDirLabel_.c_str()))
			{
				ScopeGuard endNewDirPopup([] {ImGui::EndPopup(); });

				ImGui::InputText("name", newDirNameBuf_->data(), newDirNameBuf_->size()); ImGui::SameLine();
				if (ImGui::Button("ok") && (*newDirNameBuf_)[0] != '\0')
				{
					ScopeGuard closeNewDirPopup([] { ImGui::CloseCurrentPopup(); });
					if (create_directory(pwd_ / newDirNameBuf_->data()))
						SetPwd(pwd_);
					else
						statusStr_ = "failed to create " + std::string(newDirNameBuf_->data());
				}
			}
		}

		// browse files in a child window

		float reserveHeight = ImGui::GetItemsLineHeightWithSpacing();
		std::filesystem::path newPwd; bool setNewPwd = false;
		if (!(flags_ & ImGuiFileBrowserFlags_SelectDirectory) && (flags_ & ImGuiFileBrowserFlags_EnterNewFilename))
			reserveHeight += ImGui::GetItemsLineHeightWithSpacing();
		{
			ImGui::BeginChild("ch", ImVec2(0, -reserveHeight), true,
				(flags_ & ImGuiFileBrowserFlags_NoModal) ? ImGuiWindowFlags_AlwaysHorizontalScrollbar : 0);
			ScopeGuard endChild([] {ImGui::EndChild(); });

			for (auto& rsc : fileRecords_)
			{
				const bool selected = selectedFilename_ == rsc.name;
				if (ImGui::Selectable(rsc.showName.c_str(), selected, ImGuiSelectableFlags_DontClosePopups))
				{
					if (selected)
					{
						selectedFilename_ = std::string();
						(*inputNameBuf_)[0] = '\0';
					}
					else if (rsc.name != "..")
					{
						if ((rsc.isDir && (flags_ & ImGuiFileBrowserFlags_SelectDirectory)) ||
							(!rsc.isDir && !(flags_ & ImGuiFileBrowserFlags_SelectDirectory)))
						{
							selectedFilename_ = rsc.name;
							if (!(flags_ & ImGuiFileBrowserFlags_SelectDirectory))
								std::strcpy(inputNameBuf_->data(), selectedFilename_.c_str());
						}
					}
				}

				if (ImGui::IsItemClicked(0) && ImGui::IsMouseDoubleClicked(0) && rsc.isDir)
				{
					setNewPwd = true;
					newPwd = (rsc.name != "..") ? (pwd_ / rsc.name) : pwd_.parent_path();
				}
			}
		}

		if (setNewPwd)
			SetPwd(newPwd);

		if (!(flags_ & ImGuiFileBrowserFlags_SelectDirectory) && (flags_ & ImGuiFileBrowserFlags_EnterNewFilename))
		{
			ImGui::PushID(this);
			ScopeGuard popTextID([] { ImGui::PopID(); });

			ImGui::PushItemWidth(-1);
			if (ImGui::InputText("", inputNameBuf_->data(), inputNameBuf_->size()))
				selectedFilename_ = inputNameBuf_->data();
			ImGui::PopItemWidth();
		}

		if (!(flags_ & ImGuiFileBrowserFlags_SelectDirectory))
		{
			if (ImGui::Button(" ok ") && !selectedFilename_.empty())
			{
				ok_ = true;
				ImGui::CloseCurrentPopup();
			}
		}
		else
		{
			if (selectedFilename_.empty())
			{
				if (ImGui::Button(" ok "))
				{
					ok_ = true;
					ImGui::CloseCurrentPopup();
				}
			}
			else if (ImGui::Button("open"))
				SetPwd(pwd_ / selectedFilename_);
		}

		ImGui::SameLine();

		int escIdx = ImGui::GetIO().KeyMap[ImGuiKey_Escape];
		if (ImGui::Button("cancel") || closeFlag_ ||
			((flags_ & ImGuiFileBrowserFlags_CloseOnEsc) && ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows) && escIdx >= 0 && ImGui::IsKeyPressed(escIdx)))
			ImGui::CloseCurrentPopup();

		if (!statusStr_.empty() && !(flags_ & ImGuiFileBrowserFlags_NoStatusBar))
		{
			ImGui::SameLine();
			ImGui::Text("%s", statusStr_.c_str());
		}
	}

	inline bool renderx::ui::ImguiFileBrowser::HasSelected() const noexcept
	{
		return ok_;
	}

	inline bool renderx::ui::ImguiFileBrowser::SetPwd(const std::filesystem::path& pwd)
	{
		try
		{
			SetPwdUncatched(pwd);
			return true;
		}
		catch (const std::exception& err)
		{
			statusStr_ = std::string("last error: ") + err.what();
		}
		catch (...)
		{
			statusStr_ = "last error: unknown";
		}

		SetPwdUncatched(std::filesystem::current_path());
		return false;
	}

	inline std::filesystem::path renderx::ui::ImguiFileBrowser::GetSelected() const
	{
		return pwd_ / selectedFilename_;
	}

	inline void renderx::ui::ImguiFileBrowser::ClearSelected()
	{
		selectedFilename_ = std::string();
		(*inputNameBuf_)[0] = '\0';
		ok_ = false;
	}

	inline void renderx::ui::ImguiFileBrowser::SetPwdUncatched(const std::filesystem::path& pwd)
	{
		fileRecords_ = { FileRecord{ true, "..", "[D] .." } };

		for (auto& p : std::filesystem::directory_iterator(pwd))
		{
			FileRecord rcd;

			if (p.is_regular_file())
				rcd.isDir = false;
			else if (p.is_directory())
				rcd.isDir = true;
			else
				continue;

			rcd.name = p.path().filename().string();
			if (rcd.name.empty())
				continue;

			rcd.showName = (rcd.isDir ? "[D] " : "[F] ") + p.path().filename().u8string();
			fileRecords_.push_back(rcd);
		}

		std::sort(fileRecords_.begin(), fileRecords_.end(),
			[](const FileRecord& L, const FileRecord& R)
			{
				return (L.isDir ^ R.isDir) ? L.isDir : (L.name < R.name);
			});

		pwd_ = absolute(pwd);
		selectedFilename_ = std::string();
		(*inputNameBuf_)[0] = '\0';
	}
}
