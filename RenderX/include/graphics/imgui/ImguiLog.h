#pragma once
#include "..//..//..//Core.h"

namespace renderx {
	namespace ui {
		struct REN_API LogKind
		{
			std::string initialization;
			std::string mouse;
			std::string keyboard;
			std::string window;
		};

		class REN_API ImguiLog
		{
		private:
			utils::AppLog m_AppLog;
			bool p_open = true;
		public:
			ImguiLog();
			~ImguiLog();

			void BeginLog();
			void Log();

			void EndLog();
			
		};
	}
}






