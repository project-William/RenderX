#pragma once
#include "..//..//..//Core.h"
#include "..//Window.h"
#include "..//..//entity/FPSCamera.h"
#include "..//..//entity/MayaCamera.h"
#include "..//render/RenderObject.h"

namespace renderx {
	namespace ui {

		class REN_API ImguiSetWindow
		{
		public:
			ImguiSetWindow();
			~ImguiSetWindow();

			void BeginSetWindow();
			void GraphicsSettingWindow();
			void CameraSetting(const graphics::WinData& windata, std::pair<entity::FPSCamera*, entity::MayaCamera*> campair);
			void ShowDemo() { bool a = true; ImGui::ShowDemoWindow(&a); }
			void EndSetWindow();
			void PushRenderers(std::unordered_map<graphics::RenderObject*, bool>& m_Renderer);

		private:

			void DockSpace(bool& dockopen);
		private:
			bool m_DockSpace_Open = true;
		};
	}
}