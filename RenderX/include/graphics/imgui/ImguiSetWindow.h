#pragma once
#include "..//..//..//Core.h"
#include "..//Window.h"
#include "..//render/RenderObject.h"
#include "..//RenderLayer.h"

namespace renderx {
	using CamPair=std::pair<entity::FPSCamera*, entity::MayaCamera*>;

	namespace ui {

		class REN_API ImguiSetWindow
		{
		public:
			ImguiSetWindow();
			~ImguiSetWindow();

			void BeginSetWindow();
			void GraphicsSettingWindow();
			void CameraSetting(const graphics::WinData& windata, CamPair& campair, graphics::RenderLayer& layer);
			void ShowDemo() { bool a = true; ImGui::ShowDemoWindow(&a); }
			void EndSetWindow();

		private:

			void DockSpace(bool& dockopen);
		private:
			bool m_DockSpace_Open = true;
		};
	}
}