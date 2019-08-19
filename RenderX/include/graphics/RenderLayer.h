#pragma once
#include "Layer.h"
#include "FrameBuffer.h"
#include "Renderers.h"
#include "imgui/ImguiFileBrowser.h"

namespace renderx {
	namespace graphics {

#define SINGLE_CHOICE(a,b,c,d) if(a) { b=c=d=false; }


		struct REN_API CameraPart
		{
			bool fpsCamera = false;
			bool MayaCamera = false;
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
			bool LightPBR = false;
			bool TexturePBR = false;
		};

		struct REN_API TexturePart
		{
			bool AlbedoTex = false;
			bool MetallicTex = false;
			bool AOTex = false;
			bool NormalTex = false;
			bool RoughnessTex = false;
		};

		struct REN_API EnableTexture
		{
			bool EnableAlbedo = false;
			bool EnableAO = false;
			bool EnableMetallic = false;
			bool EnableNormal = false;
			bool EnableRoughness = false;
		};

		class REN_API RenderLayer:public Layer
		{
		public:
			RenderLayer();
			~RenderLayer();

			void PushRenderer(RenderObject* renderer, bool isRendered);
			void PushFlatboard(entity::Flatboard* flatboard);
			void DoRendering(const WinData& windata);
			void RenderSettings(const WinData& windata, entity::FPSCamera* camera, RenderLight* light);
			void CameraSetting(const WinData& windata, entity::FPSCamera* camera);
			void DefaultCamSet(const WinData& windata, std::pair<entity::FPSCamera*, entity::MayaCamera*> campair);
			void File();
			

			void RenderSkybox(const WinData& windata, entity::FPSCamera* camera);
			void DefSkybox(const WinData& windata, entity::MayaCamera* camera);
			void RenderFlatboard(const WinData& windata,entity::FPSCamera* camera, RenderLight* light);
			
			void RenderObjects(const WinData& windata, entity::FPSCamera* camera);
			void LightModel(RenderLight* light, entity::FPSCamera* camera);
			void RenderModel();
			void OnAttach() override;
			void OnDetach() override;
			void OnImguiLayer() override;
			void PushSkybox(entity::RenderSkybox* skybox);
			void PushLights(graphics::RenderLight* light);
			//skybox 
			void InitCamera(entity::FPSCamera* fpscam, entity::MayaCamera* defcam);
				
		private:
			ui::ImguiFileBrowser m_FileBrowser;

			std::unordered_map<RenderObject*, bool> m_Renderer;
			std::vector<entity::RenderSkybox*> m_Skyboxes;
			std::vector<entity::Flatboard*> m_Flatboards;
			std::pair<entity::FPSCamera*, entity::MayaCamera*> m_Camera;
			std::vector<RenderLight*> m_Lights;
			

			bool m_DockSpace_Open = true;
			bool m_Skybox_App_Open = false;
			bool m_Renderer_App_Open = true;
			bool m_Light_App_Open = false;
			bool m_Renderer_Attrib_App_Open = false;
			bool m_Texture_App_Open = false;
			bool m_Other_Attrib_App_Open = false;
			bool m_LightModel_Open = false;

			float m_gamma_value = 2.2f;
			bool m_Open_MSAA = false;

			bool EnvirMapping = false;

			std::shared_ptr<Texture> m_EmptyTexture;

			float m_metallic = 0.5f;
			float m_roughness = 0.25f;

			std::string name;

			SkyboxPart m_SkyboxPart;
			CameraPart m_CameraPart;
			RendererPart m_RendererPart;
			LightPart m_LightPart;
			LightModelPart m_LightModelPart;
			TexturePart m_TexturePart;
			EnableTexture m_EnableTexture;

			bool isUse = false;


		private:
			void EmptyTexture(const std::string& filepath);
		};

	}
}