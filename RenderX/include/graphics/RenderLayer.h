#pragma once
#include "Layer.h"
#include "FrameBuffer.h"
#include "Renderers.h"
#include "imgui/ImguiFileBrowser.h"

namespace renderx {

	using CamPair=std::pair<entity::FPSCamera*, entity::MayaCamera*>;

	namespace graphics {


		struct REN_API CameraPart
		{
			bool fpsCamera = false;
			bool MayaCamera = true;
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
			bool Blinn_Phong = true;
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
			void CameraSettng(const WinData& windata, CamPair& campair);

			void RenderSkybox(const WinData& windata, CamPair& camera);
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
				
			inline std::unordered_map<RenderObject*, bool>& GetRenderersRef() { return m_Renderer; }
			inline SkyboxPart& IsSkyboxRenderRef() { return m_SkyboxPart; }
			inline CameraPart& IsCameraRef() { return m_CameraPart; }
			inline RendererPart& IsRenderRef() { return m_RendererPart; }
			inline LightModelPart& IsLightModeRef() { return m_LightModelPart; }
			inline TexturePart& IsTextureRef() { return m_TexturePart; }
			inline EnableTexture& IsEnableTextureRef() { return m_EnableTexture; }
			inline ui::ImguiFileBrowser& GetFileBrowser() { return m_FileBrowser; }
			inline std::shared_ptr<Texture>& GetEmptyTextureRef() { return m_EmptyTexture; }
		private:
			ui::ImguiFileBrowser m_FileBrowser;

			std::unordered_map<RenderObject*, bool> m_Renderer;
			std::vector<entity::RenderSkybox*> m_Skyboxes;
			std::vector<entity::Flatboard*> m_Flatboards;
			CamPair m_Camera;
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
		};

	}
}