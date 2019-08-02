#include "graphics/RenderLayer.h"

namespace renderx {
	namespace graphics {

		RenderLayer::RenderLayer()
		{

		}

		RenderLayer::RenderLayer(const WinData& windata)
		{

		}

		RenderLayer::~RenderLayer()
		{
		}


		void RenderLayer::PushBackRenderer(RenderObject* renderer)
		{
			m_Renderers.push_back(renderer);
		}

		void RenderLayer::DoRendering(const WinData& windata)
		{
			for (auto renderer : m_Renderers)
			{
				renderer->Draw(windata);
			}
		}


		void RenderLayer::RenderSettings()
		{

			if (ImGui::CollapsingHeader("FPS Game Camera"))
			{
				float s=1;
				ImGui::SliderFloat("Mouse Sensitivity", &s,0.01f,0.5f);
				
			}
			if (ImGui::CollapsingHeader("Skybox"))
			{
				if (ImGui::Checkbox("Skybox 1", &m_SkyboxPart.skybox_1))
				{
					SINGLE_CHOICE(m_SkyboxPart.skybox_1, m_SkyboxPart.skybox_2, m_SkyboxPart.skybox_3, m_SkyboxPart.skybox_4);
				}

				if (ImGui::Checkbox("Skybox 2", &m_SkyboxPart.skybox_2))
				{
					SINGLE_CHOICE(m_SkyboxPart.skybox_2, m_SkyboxPart.skybox_1, m_SkyboxPart.skybox_3, m_SkyboxPart.skybox_4);
				}

				if (ImGui::Checkbox("Skybox 3", &m_SkyboxPart.skybox_3))
				{
					SINGLE_CHOICE(m_SkyboxPart.skybox_3, m_SkyboxPart.skybox_1, m_SkyboxPart.skybox_2, m_SkyboxPart.skybox_4);

				}

				if (ImGui::Checkbox("Skybox 4", &m_SkyboxPart.skybox_4))
				{
					SINGLE_CHOICE(m_SkyboxPart.skybox_4, m_SkyboxPart.skybox_1, m_SkyboxPart.skybox_3, m_SkyboxPart.skybox_2);
				}

				
								
			}

			//renderers header
			if(ImGui::CollapsingHeader("Renderers", m_Renderer_App_Open))
			{

				if (ImGui::Checkbox("Cube", &m_RendererPart.renderer_1))
				{
					SINGLE_CHOICE(m_RendererPart.renderer_1, m_RendererPart.renderer_2, m_RendererPart.renderer_3, m_RendererPart.renderer_4);
				}

				if (ImGui::Checkbox("Sphere", &m_RendererPart.renderer_2))
				{
					SINGLE_CHOICE(m_RendererPart.renderer_2, m_RendererPart.renderer_1, m_RendererPart.renderer_3, m_RendererPart.renderer_4);
				}

				if (ImGui::Checkbox("Model_1", &m_RendererPart.renderer_3))
				{
					SINGLE_CHOICE(m_RendererPart.renderer_3, m_RendererPart.renderer_2, m_RendererPart.renderer_1, m_RendererPart.renderer_4);
				}

				if (ImGui::Checkbox("Model_2", &m_RendererPart.renderer_4))
				{
					SINGLE_CHOICE(m_RendererPart.renderer_4, m_RendererPart.renderer_2, m_RendererPart.renderer_3, m_RendererPart.renderer_1);
				}

			}
			//lights
			if(ImGui::CollapsingHeader("Lights", m_Light_App_Open))
			{
				if (ImGui::Checkbox("Light_1", &m_LightPart.light_1))
				{
					SINGLE_CHOICE(m_LightPart.light_1, m_LightPart.light_2, m_LightPart.light_3, m_LightPart.light_4);
				}
				if (ImGui::Checkbox("Light_2", &m_LightPart.light_2))
				{
					SINGLE_CHOICE(m_LightPart.light_2, m_LightPart.light_1, m_LightPart.light_3, m_LightPart.light_4);
				}
				if (ImGui::Checkbox("Light_3", &m_LightPart.light_3))
				{
					SINGLE_CHOICE(m_LightPart.light_3, m_LightPart.light_2, m_LightPart.light_1, m_LightPart.light_4);
				}
				if (ImGui::Checkbox("Light_4", &m_LightPart.light_4))
				{
					SINGLE_CHOICE(m_LightPart.light_4, m_LightPart.light_2, m_LightPart.light_3, m_LightPart.light_1);
				}
			}
			//renderers attributes
			if(ImGui::CollapsingHeader("Renderers Attributes", m_Renderer_App_Open))
			{
				float color[4];
				float pos[3];
				float scale;
				ImGui::ColorEdit4("Render Color", &color[0]);
				ImGui::SliderFloat("Position-x", &pos[0], -20, 20);
				ImGui::SliderFloat("Position-y", &pos[1], -20, 20);
				ImGui::SliderFloat("Position-z", &pos[2], -20, 20);
				ImGui::SliderFloat("Scale", &scale, 0.1f, 5.0f);
			}

			//texture
			if(ImGui::CollapsingHeader("Textures", m_Texture_App_Open))
			{
				ImGui::Text("texture1");
				ImGui::Text("texture2");
				ImGui::Text("texture3");
				ImGui::Text("texture4");
			}

			//other attributes
			if(ImGui::CollapsingHeader("Other Attributes", m_Other_Attrib_App_Open))
			{
				ImGui::Text("HDR");
			}
		}

		void RenderLayer::RenderSkybox(const WinData& windata, entity::FPSCamera* camera)
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
			ImGuiWindowFlags window_flags = false;

			bool show = true;
			if (!ImGui::Begin("RenderX Settings", &show, window_flags))
			{
				// Early out if the window is collapsed, as an optimization.
				ImGui::End();
				return;
			}

			ImGui::End();
		}

		
		void RenderLayer::InitCamera(entity::FPSCamera* fpscam, entity::DefaultCamera* defcam)
		{
			m_Camera.first = fpscam;
			m_Camera.second = defcam;
		}

		void RenderLayer::PushSkybox(entity::RenderSkybox* skybox)
		{
			m_Skyboxes.push_back(skybox);
		}
		
	}
}
