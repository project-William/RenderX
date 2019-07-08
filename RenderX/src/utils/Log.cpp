#include "utils/Log.h"

namespace renderx {
	namespace utils {
		void Log::LogInit(const char* func, const char* file, int line, const char* format, ...)
		{
			std::cout << "[function:" << func;
			std::cout << "] [File:" << file;
			std::cout << "] [Line:" << line << "]" << std::endl;
			va_list args;
			va_start(args, format);
			vprintf(format, args);
			va_end(args);
		}
	}
}