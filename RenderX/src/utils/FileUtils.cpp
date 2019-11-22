#include "utils/FileUtils.h"

namespace renderx {
	namespace utils {

		const std::string FileUtils::ReadFile(const std::string& filepath)
		{
			std::ifstream infile(filepath);
			if (infile)
			{
				std::stringstream strstream;
				strstream << infile.rdbuf();
				std::string result = strstream.str();
				return result;
			}
			return "";
		}


	}
}