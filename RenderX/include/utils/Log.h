#pragma once
#include <iostream>
#include <string>
#include <stdarg.h>

namespace renderx {
	namespace utils {
		class Log
		{
		public:
			static void LogInit(const char* func, const char* file, int line,const char* format, ...)
			{
				std::cout << "[function:" << func;
				std::cout << "] [File:" << file ;
				std::cout << "] [Line:" << line <<"]";
				va_list args;
				va_start(args, format);
				vprintf(format, args);
				va_end(args);
			}
		};
	}
}