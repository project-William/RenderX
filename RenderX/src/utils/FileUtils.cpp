#include "utils/FileUtils.h"


namespace renderx {
	namespace utils {

		std::optional<std::string> FileUtils::ReadShader(const std::string& filepath)
		{
			std::ifstream infile(filepath);
			if (infile)
			{
				std::stringstream strstream;
				strstream << infile.rdbuf();
				std::string result = strstream.str();
				return result;
			}
			return std::nullopt;
		}


	}
}