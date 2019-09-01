#pragma once
#include "..//..//Core.h"

namespace renderx {
	namespace utils {
		class REN_API FileUtils
		{
		public:
			static std::optional<std::string> ReadShader(const std::string& filepath);

		};
	}
}