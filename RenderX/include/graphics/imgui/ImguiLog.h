#pragma once
#include "ImguiLayer.h"

namespace renderx {
	namespace graphics {
		
		class REN_API ImguiLog
		{
		public:
			ImguiLog();
			~ImguiLog();

			void BeginLog();
			void EndLog();


		};

	}
}