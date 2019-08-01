#pragma once
#include "Layer.h"
#include "FrameBuffer.h"
#include "Renderers.h"

namespace renderx {
	namespace graphics {

#define SINGLE_CHOICE(a,b,c,d) if(a) { b=c=d=false; }

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

			void PushFrontRenderer(RenderObject* renderer);
			void PushBackRenderer(RenderObject* renderer);

			void DoRendering(const WinData& windata);


			void RenderSettings();

			void RenderSkybox();
			void RenderModel();
			void OnAttach() override;
			void OnDetach() override;
			void OnImguiLayer() override;

			//skybox 
			void PushbackSkybox();
			void PushfrontSkybox();
			//renderers
			void PushbackRenderers();
			void PushfrontRenderers();

		private:
			std::list<RenderObject*> m_Renderers;
			RenderObject* m_Render;
			
			std::list<entity::RenderSkybox> m_RenderSkybox;
			

			bool m_DockSpace_Open = true;
			bool m_Skybox_App_Open = false;
			bool m_Renderer_App_Open = true;
			bool m_Light_App_Open = false;
			bool m_Renderer_Attrib_App_Open = false;
			bool m_Texture_App_Open = false;
			bool m_Other_Attrib_App_Open = false;

			SkyboxPart m_SkyboxPart;
			RendererPart m_RendererPart;
			LightPart m_LightPart;
			
		};

	}
}