#pragma once
#include "..//..//..//Core.h"


namespace renderx {
	namespace ui {

		struct REN_API FileInfo
		{
			char type;
			std::string filepath;
			std::string filename;
			std::string ext;
		};

		class REN_API ImguiFileDialog
		{
		private:
			std::vector<FileInfo> m_FileList;
			std::string m_SelectedFileName;
			std::string m_CurrentPath;
			std::vector<std::string> m_CurrentPathDeComposition;
			std::string m_CurrentFilterExt;
			static std::shared_ptr<ImguiFileDialog> m_FileDialog;
		private:
			static char FileNameBuffer[MAX_FILE_DIALOG_NAME_BUFFER];
			static int FilterIndex;
			bool IsoOk;
			static std::shared_ptr<ImguiFileDialog> Create();
			
		public:
			
			ImguiFileDialog();
			~ImguiFileDialog();

			inline std::shared_ptr<ImguiFileDialog> GetImguiFileDialogInstance()
			{
				return m_FileDialog;
			}

			bool FileDialog(const char* name, const char* filters = 0, std::string path = "", std::string defaultName = "");
			std::string GetFilePathName();
			std::string GetCurrentPath();
			std::string GetCurrentFileName();
			std::string GetCurrentFilter();
		private:
			void ScanDir(std::string path);
			void SetCurrentDir(std::string path);
			void ComposeNewPath(std::vector<std::string>::iterator iter);


		};
	}
}