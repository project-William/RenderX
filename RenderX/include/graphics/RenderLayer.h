#pragma once
#include "Layer.h"
#include "FrameBuffer.h"
#include "Renderers.h"

namespace renderx {
	namespace graphics {

#define SINGLE_CHOICE(a,b,c,d) if(a) { b=c=d=false; }

		using Camera_Pair=std::pair<entity::FPSCamera*, entity::DefaultCamera*>;

		struct REN_API SkyboxPart
		{
			bool skybox_1 = true;
			bool skybox_2 = false;
			bool skybox_3 = false;
			bool skybox_4 = false;
		};
		struct REN_API LightPart
		{
			bool light_1 = true;
			bool light_2 = false;
			bool light_3 = false;
			bool light_4 = false;
		};
		struct REN_API RendererPart
		{
			bool renderer_1 = true;
			bool renderer_2 = false;
			bool renderer_3 = false;
			bool renderer_4 = false;
		};

		class REN_API RenderLayer:public Layer
		{
		public:
			RenderLayer();
			RenderLayer(const WinData& windata);
			~RenderLayer();

			void PushBackRenderer(RenderObject* renderer);

			void DoRendering(const WinData& windata);

			void RenderSettings();

			void RenderSkybox(const WinData& windata, entity::FPSCamera* camera);
			void RenderModel();
			void OnAttach() override;
			void OnDetach() override;
			void OnImguiLayer() override;
			void PushSkybox(entity::RenderSkybox* skybox);

			//skybox 
			void InitCamera(entity::FPSCamera* fpscam, entity::DefaultCamera* defcam);
		
		private:

			std::vector<RenderObject*> m_Renderers;
			
			entity::RenderSkybox* m_Skybox;

			std::vector<entity::RenderSkybox*> m_Skyboxes;

			std::pair<entity::FPSCamera*, entity::DefaultCamera*> m_Camera;

			int skybox_flags = 1;



			bool m_DockSpace_Open = true;
			bool m_Skybox_App_Open = false;
			bool m_Renderer_App_Open = true;
			bool m_Light_App_Open = false;
			bool m_Renderer_Attrib_App_Open = false;
			bool m_Texture_App_Open = false;
			bool m_Other_Attrib_App_Open = false;

			SkyboxPart m_SkyboxPart;
			
			bool skyboxchoice1 = true;
			bool skyboxchoice2 = false;
			bool skyboxchoice3 = false;
			bool skyboxchoice4 = false;
			
			
			RendererPart m_RendererPart;
			LightPart m_LightPart;
			
		};

	}
}