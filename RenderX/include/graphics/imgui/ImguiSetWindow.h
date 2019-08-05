#pragma once
#include "..//..//..//Core.h"

namespace renderx {
	namespace ui {

		class REN_API ImguiSetWindow
		{
		public:
			ImguiSetWindow();
			~ImguiSetWindow();

			void BeginSetWindow();
			void GraphicsSettingWindow();
			void ShowDemo() { bool a = true; ImGui::ShowDemoWindow(&a); }
			void EndSetWindow();

		private:
			void DockSpace(bool& dockopen);
		private:
			bool m_DockSpace_Open = true;
		};
	}
}