#include "graphics/imgui/ImguiFileDialog.h"

namespace renderx {
	namespace ui {

		std::shared_ptr<ImguiFileDialog> ImguiFileDialog::m_FileDialog = nullptr;

		std::shared_ptr<ImguiFileDialog> ImguiFileDialog::Create()
		{
			if (m_FileDialog)
			{
				m_FileDialog = std::shared_ptr<ImguiFileDialog>(new ImguiFileDialog());
				return m_FileDialog;
			}

			return m_FileDialog;
		}

		ImguiFileDialog::ImguiFileDialog()
		{
		}

		ImguiFileDialog::~ImguiFileDialog()
		{
		}

		bool ImguiFileDialog::FileDialog(const char* name, const char* filters, std::string path, std::string defaultName)
		{
			return false;
		}

		std::string ImguiFileDialog::GetFilePathName()
		{
			return std::string();
		}

		std::string ImguiFileDialog::GetCurrentPath()
		{
			return std::string();
		}

		std::string ImguiFileDialog::GetCurrentFileName()
		{
			return std::string();
		}

		std::string ImguiFileDialog::GetCurrentFilter()
		{
			return std::string();
		}

		void ImguiFileDialog::ScanDir(std::string path)
		{
		}

		void ImguiFileDialog::SetCurrentDir(std::string path)
		{
		}

		void ImguiFileDialog::ComposeNewPath(std::vector<std::string>::iterator iter)
		{
		}

	}
}