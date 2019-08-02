#pragma once
#include "Layer.h"
#include "FrameBuffer.h"
#include "Renderers.h"

namespace renderx {
	namespace graphics {

#define SINGLE_CHOICE(a,b,c,d) if(a) { b=c=d=false; }

		using Camera_Pair=std::pair<entity::FPSCamera*, entity::DefaultCamera*>;

		struct REN_API CameraPart
		{
			bool fpsCamera = false;
			bool defaultCamera = false;
			bool NoCamera = true;
		};

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

		struct REN_API LightModelPart
		{
			bool PhongModel = true;
			bool Blinn_Phong = false;
		};

		class REN_API RenderLayer:public Layer
		{
		public:
			RenderLayer();
			RenderLayer(const WinData& windata);
			~RenderLayer();

			void PushRenderer(RenderObject* renderer, bool isRendered);
			void DoRendering(const WinData& windata);
			void RenderSettings(const WinData& windata, entity::FPSCamera* camera, RenderLight* light);
			void CameraSetting(const WinData& windata, entity::FPSCamera* camera);

			void RenderSkybox(const WinData& windata, entity::FPSCamera* camera);
			void RenderObjects(const WinData& windata, entity::FPSCamera* camera);
			void LightModel(RenderLight* light, entity::FPSCamera* camera);
			void RenderModel();
			void OnAttach() override;
			void OnDetach() override;
			void OnImguiLayer() override;
			void PushSkybox(entity::RenderSkybox* skybox);

			//skybox 
			void InitCamera(entity::FPSCamera* fpscam, entity::DefaultCamera* defcam);
				
		private:

			std::unordered_map<RenderObject*, bool> m_Renderer;

			std::vector<RenderObject*> m_Renderers;
			
			entity::RenderSkybox* m_Skybox;

			std::vector<entity::RenderSkybox*> m_Skyboxes;

			std::pair<entity::FPSCamera*, entity::DefaultCamera*> m_Camera;

			bool m_DockSpace_Open = true;
			bool m_Skybox_App_Open = false;
			bool m_Renderer_App_Open = true;
			bool m_Light_App_Open = false;
			bool m_Renderer_Attrib_App_Open = false;
			bool m_Texture_App_Open = false;
			bool m_Other_Attrib_App_Open = false;
			bool m_LightModel_Open = false;
			SkyboxPart m_SkyboxPart;
			CameraPart m_CameraPart;
			RendererPart m_RendererPart;
			LightPart m_LightPart;
			LightModelPart m_LightModelPart;
		};

	}
}