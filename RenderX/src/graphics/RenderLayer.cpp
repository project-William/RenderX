#include "graphics/RenderLayer.h"

namespace renderx {
	namespace graphics {

		RenderLayer::RenderLayer()
		{
			m_EmptyTexture = std::shared_ptr<Texture>(new Texture("Empty Texture", "texture/EmptyTexture.png"));
		}

		RenderLayer::~RenderLayer()
		{
		}

		void RenderLayer::PushRenderer(RenderObject* renderer, bool isRendered)
		{
			m_Renderer.insert(std::pair<RenderObject*, bool>(renderer,isRendered));
		}

		void RenderLayer::PushFlatboard(entity::Flatboard* flatboard)
		{
			m_Flatboards.push_back(flatboard);
		}

		void RenderLayer::LightModel(RenderLight* light, entity::FPSCamera* camera)
		{
			bool istex = true;
			for (auto& iter : m_Renderer)
			{
				if (iter.second)
				{
					iter.first->GetRenderDataRef()->m_Shader->SetVec4("u_color", iter.first->GetTransRef().color);
					iter.first->GetRenderDataRef()->m_Shader->SetVec3("u_lightColor", light->GetLightColor());
					iter.first->GetRenderDataRef()->m_Shader->SetVec3("u_lightPos", light->GetLightPosition());
					iter.first->GetRenderDataRef()->m_Shader->SetVec3("u_viewPos", camera->GetCameraAttrib().Position);
					iter.first->GetRenderDataRef()->m_Shader->SetFloat("u_Shineness", light->GetShineness());
					iter.first->GetRenderDataRef()->m_Shader->SetBool("u_blinn_phong", m_LightModelPart.Blinn_Phong);
					iter.first->GetRenderDataRef()->m_Shader->SetFloat("u_gamma_value", m_gamma_value);
					iter.first->GetRenderDataRef()->m_Shader->SetBool("u_light_pbr", m_LightModelPart.LightPBR);
					iter.first->GetRenderDataRef()->m_Shader->SetBool("u_texture_pbr", m_LightModelPart.TexturePBR);
					iter.first->GetRenderDataRef()->m_Shader->SetFloat("u_metallic", m_metallic);
					iter.first->GetRenderDataRef()->m_Shader->SetFloat("u_roughness", m_roughness);
					iter.first->GetRenderDataRef()->m_Shader->SetBool("u_IsBlinnTexture", istex);
					iter.first->UnbindObject();
				}
			}
		}

		void RenderLayer::RenderSkybox(const WinData& windata, CamPair& camera)
		{
			if (m_SkyboxPart.skybox_1)
			{
				m_Skyboxes[0]->Draw(windata, camera);
			}
			if (m_SkyboxPart.skybox_2)
			{
				m_Skyboxes[1]->Draw(windata, camera);
			}
			if (m_SkyboxPart.skybox_3)
			{
				m_Skyboxes[2]->Draw(windata, camera);
			}
			if (m_SkyboxPart.skybox_4)
			{
				m_Skyboxes[3]->Draw(windata, camera);
			}
		}

		void RenderLayer::RenderFlatboard(const WinData& windata, entity::FPSCamera* camera, RenderLight* light)
		{
			for (auto iter : m_Flatboards)
			{
				iter->EnableObject();
			
				iter->GetRenderDataRef()->m_Shader->SetVec3("u_lightColor", light->GetLightColor());
				iter->GetRenderDataRef()->m_Shader->SetVec3("u_lightPos", light->GetLightPosition());
				iter->GetRenderDataRef()->m_Shader->SetVec3("u_viewPos", camera->GetCameraAttrib().Position);
				iter->Draw(windata, camera);
			
				iter->DisableObject();
			}
		}

		void RenderLayer::RenderObjects(const WinData& windata, entity::FPSCamera* camera)
		{
			auto iter = m_Renderer.begin();
			if (m_RendererPart.renderer_1)
			{
				iter->first->Draw(windata);
			}
			
			if (m_RendererPart.renderer_2)
			{
				(++iter)->first->Draw(windata);
			}
			
			if (m_RendererPart.renderer_3)
			{
				
			}
			
			if (m_RendererPart.renderer_4)
			{

			}
		}

		void RenderLayer::RenderModel()
		{
		}

		void RenderLayer::OnAttach()
		{
		}

		void RenderLayer::OnDetach()
		{
		}

	
		void RenderLayer::OnImguiLayer()
		{
		}
		
		void RenderLayer::InitCamera(entity::FPSCamera* fpscam, entity::MayaCamera* defcam)
		{
			m_Camera.first = fpscam;
			m_Camera.second = defcam;
		}

		void RenderLayer::PushSkybox(entity::RenderSkybox* skybox)
		{
			m_Skyboxes.push_back(skybox);
		}

		void RenderLayer::PushLights(graphics::RenderLight* light)
		{
			m_Lights.push_back(light);
		}


	}
}
