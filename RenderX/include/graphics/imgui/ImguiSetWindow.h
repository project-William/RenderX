#pragma once
#include "ImguiLayer.h"

namespace renderx {
	namespace graphics {

		class REN_API ImguiSetWindow
		{
		public:
			ImguiSetWindow();
			~ImguiSetWindow();

			void BeginSetWindow();
			void GraphicsSettingWindow();
			void EndSetWindow();

		private:
			void DockSpace(bool& dockopen);
		private:
			bool m_DockSpace_Open = true;
		};
	}
}