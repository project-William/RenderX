#include "utils/FileUtils.h"


namespace renderx {
	namespace utils {
		std::string FileUtils::read_shader(const std::string& filepath)
		{
			std::ifstream infile(filepath);
			std::stringstream ss;
			if (!infile.is_open())
				throw std::runtime_error("Unable to open the file" + filepath);
			else
			{
				ss << infile.rdbuf();
				return ss.str();
			}
		}
	}
}