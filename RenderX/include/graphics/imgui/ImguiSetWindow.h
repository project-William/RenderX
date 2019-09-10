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
			void Setting(const graphics::WinData& windata, CamPair& campair, graphics::RenderLayer& layer);
			void CameraSetting(CamPair& camPair, graphics::RenderLayer& layer, const graphics::WinData& windata);
			void ShowDemo() { bool a = true; ImGui::ShowDemoWindow(&a); }
			void EndSetWindow();

		private:
			bool m_DockSpace_Open = true;
			bool m_Skybox_App_Open = false;
			bool m_Renderer_App_Open = true;
			bool m_Light_App_Open = false;
			bool m_Renderer_Attrib_App_Open = false;
			bool m_Texture_App_Open = false;
			bool m_Other_Attrib_App_Open = false;
			bool m_LightModel_Open = false;
			void DockSpace(bool& dockopen);
			ImguiFileBrowser m_FileBrowser;


		private:
		

			void CameraHeader(graphics::RenderLayer& layer);
			void SkyboxHeader(graphics::RenderLayer& layer);
			void RendererHeader(graphics::RenderLayer& layer);
			void LightModelHeader(graphics::RenderLayer& layer);
			void TextureHeader(graphics::RenderLayer& layer);
			void OtherAttribHeader(graphics::RenderLayer& layer);
		};
	}
}