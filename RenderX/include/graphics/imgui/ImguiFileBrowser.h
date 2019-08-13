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

	
}
