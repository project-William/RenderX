#pragma once
#include <iostream>
#include <string>
#include <stdarg.h>

namespace renderx {
	namespace utils {
		class Log
		{
		public:
			static void LogInit(const char* func, const char* file, int line, const char* format, ...);
		};
	}
}