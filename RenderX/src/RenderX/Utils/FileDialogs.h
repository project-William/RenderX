#pragma once
#include "pch.h"


namespace renderx::utils 
{
	class FileDialogs
	{
	public:
		static std::string OpenFile(const std::string& path);
		static std::string GetFileName(const std::string& path);
		static std::string GetRawNameOfRenderer(const std::string& name);
	};
}