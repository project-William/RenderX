#include "pch.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <commdlg.h>
#include "FileDialogs.h"
#include "../Base/Window.h"

namespace renderx::utils
{
	std::string FileDialogs::OpenFile(const std::string& path)
	{
		OPENFILENAMEA ofn; //common dialog box structure
		CHAR szFile[260] = { 0 };
		//initialize OPENFILENAME
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = glfwGetWin32Window(base::Window::Get()->GetNativeWindow());
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = path.c_str();
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
		if (GetOpenFileNameA(&ofn) == TRUE)
		{
			return ofn.lpstrFile;
		}
	
		return std::string();
	}

	std::string FileDialogs::GetFileName(const std::string& path)
	{
		std::string name = "";
		int index = path.size() - 1;
		if (index != -1)
		{
			while (path[index] != '.')
			{
				index--;
			}
			index--;
			while (path[index] != '\\')
			{
				name += path[index];
				index--;
			}
		}

		std::reverse(name.begin(), name.end());
		return name;
	}

	std::string FileDialogs::GetRawNameOfRenderer(const std::string& name)
	{
		std::string rawName;
		int index = 0;
		while (name[index]!='_')
		{
			rawName += name[index];
			index++;
		}

		return rawName;
	}

}