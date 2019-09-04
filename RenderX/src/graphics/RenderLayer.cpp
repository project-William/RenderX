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

		void RenderLayer::DoRendering(const WinData& windata)
		{
		}

		void RenderLayer::RenderSettings(const WinData& windata, entity::FPSCamera* camera, RenderLight* light)
		{
			if (ImGui::CollapsingHeader("Camera"))
			{
				if (ImGui::Checkbox("FPS Game Camera", &m_CameraPart.fpsCamera))
				{
					if (m_CameraPart.fpsCamera)
					{
						m_CameraPart.MayaCamera = false;
						m_CameraPart.NoCamera = false;
					}
				}
				
				if (ImGui::Checkbox("Default Camera", &m_CameraPart.MayaCamera))
				{
					if (m_CameraPart.MayaCamera)
					{
						m_CameraPart.fpsCamera = false;
						m_CameraPart.NoCamera = false;
					}
				}

				if (ImGui::Checkbox("No Camera", &m_CameraPart.NoCamera))
				{
					if (m_CameraPart.NoCamera)
					{	
						m_CameraPart.fpsCamera = false;
						m_CameraPart.MayaCamera = false;
					}
				}
			}
			
			if (ImGui::CollapsingHeader("Skybox"))
			{
				if (ImGui::Checkbox("Skybox 1", &m_SkyboxPart.skybox_1))
				{
					SINGLE_CHOICE_IN_FOUR(m_SkyboxPart.skybox_1, m_SkyboxPart.skybox_2, m_SkyboxPart.skybox_3, m_SkyboxPart.skybox_4);
				}

				if (ImGui::Checkbox("Skybox 2", &m_SkyboxPart.skybox_2))
				{
					SINGLE_CHOICE_IN_FOUR(m_SkyboxPart.skybox_2, m_SkyboxPart.skybox_1, m_SkyboxPart.skybox_3, m_SkyboxPart.skybox_4);
				}

				if (ImGui::Checkbox("Skybox 3", &m_SkyboxPart.skybox_3))
				{
					SINGLE_CHOICE_IN_FOUR(m_SkyboxPart.skybox_3, m_SkyboxPart.skybox_1, m_SkyboxPart.skybox_2, m_SkyboxPart.skybox_4);
				}

				if (ImGui::Checkbox("Skybox 4", &m_SkyboxPart.skybox_4))
				{
					SINGLE_CHOICE_IN_FOUR(m_SkyboxPart.skybox_4, m_SkyboxPart.skybox_1, m_SkyboxPart.skybox_3, m_SkyboxPart.skybox_2);
				}

			}

			//renderers header
			auto RenderIter = m_Renderer.begin();
			if (ImGui::CollapsingHeader("Renderers", m_Renderer_App_Open))
			{

				if (ImGui::Checkbox("Sphere", &m_RendererPart.renderer_1))
				{
					SINGLE_CHOICE_IN_FOUR(m_RendererPart.renderer_1, m_RendererPart.renderer_2, m_RendererPart.renderer_3, m_RendererPart.renderer_4);
					RenderIter->second = m_RendererPart.renderer_1;
				}

				if (ImGui::Checkbox("cube", &m_RendererPart.renderer_2))
				{
					SINGLE_CHOICE_IN_FOUR(m_RendererPart.renderer_2, m_RendererPart.renderer_1, m_RendererPart.renderer_3, m_RendererPart.renderer_4);
					(++RenderIter)->second = m_RendererPart.renderer_1;
				}

				if (ImGui::Checkbox("Model_1", &m_RendererPart.renderer_3))
				{
					SINGLE_CHOICE_IN_FOUR(m_RendererPart.renderer_3, m_RendererPart.renderer_2, m_RendererPart.renderer_1, m_RendererPart.renderer_4);
				}

				if (ImGui::Checkbox("Model_2", &m_RendererPart.renderer_4))
				{
					SINGLE_CHOICE_IN_FOUR(m_RendererPart.renderer_4, m_RendererPart.renderer_2, m_RendererPart.renderer_3, m_RendererPart.renderer_1);
				}
			}
			//lights
			if (ImGui::CollapsingHeader("Lights", m_Light_App_Open))
			{
				if (ImGui::Checkbox("Light_1", &m_LightPart.light_1))
				{
					SINGLE_CHOICE_IN_FOUR(m_LightPart.light_1, m_LightPart.light_2, m_LightPart.light_3, m_LightPart.light_4);
				}

				if (ImGui::Checkbox("Light_2", &m_LightPart.light_2))
				{
					SINGLE_CHOICE_IN_FOUR(m_LightPart.light_2, m_LightPart.light_1, m_LightPart.light_3, m_LightPart.light_4);
				}

				if (ImGui::Checkbox("Light_3", &m_LightPart.light_3))
				{
					SINGLE_CHOICE_IN_FOUR(m_LightPart.light_3, m_LightPart.light_2, m_LightPart.light_1, m_LightPart.light_4);
				}

				if (ImGui::Checkbox("Light_4", &m_LightPart.light_4))
				{
					SINGLE_CHOICE_IN_FOUR(m_LightPart.light_4, m_LightPart.light_2, m_LightPart.light_3, m_LightPart.light_1);
				}
				
			}
			//Light model
			if (ImGui::CollapsingHeader("Light Model", m_LightModel_Open))
			{
				if (ImGui::Checkbox("Phong Model", &m_LightModelPart.PhongModel))
				{
					SINGLE_CHOICE_IN_FOUR(m_LightModelPart.PhongModel, m_LightModelPart.Blinn_Phong,
								  m_LightModelPart.LightPBR, m_LightModelPart.TexturePBR);
				}

				if (ImGui::Checkbox("Blinn Phong", &m_LightModelPart.Blinn_Phong))
				{
					SINGLE_CHOICE_IN_FOUR(m_LightModelPart.Blinn_Phong, m_LightModelPart.PhongModel,
								  m_LightModelPart.LightPBR, m_LightModelPart.TexturePBR);
				}

				if (ImGui::Checkbox("Lighting PBR", &m_LightModelPart.LightPBR))
				{
					SINGLE_CHOICE_IN_FOUR(m_LightModelPart.LightPBR, m_LightModelPart.Blinn_Phong,
								  m_LightModelPart.PhongModel, m_LightModelPart.TexturePBR);
				}
				
				if (ImGui::Checkbox("Texture PBR", &m_LightModelPart.TexturePBR))
				{
					SINGLE_CHOICE_IN_FOUR(m_LightModelPart.TexturePBR, m_LightModelPart.Blinn_Phong,
								  m_LightModelPart.LightPBR, m_LightModelPart.PhongModel);
				}

				

				for (auto light : m_Lights)
				{
					if (light)
					{
						
					}
				}

				ImGui::SliderFloat("Shineness", &light->GetShinenessRef(), 0.0f, 128.0f);
				ImGui::ColorEdit3("Light Color", &light->GetLightColorRef()[0]);
				ImGui::SliderFloat("X-axis", &light->GetLightPositionRef().x, -20, 20);
				ImGui::SliderFloat("Y-axis", &light->GetLightPositionRef().y, -20, 20);
				ImGui::SliderFloat("Z-axis", &light->GetLightPositionRef().z, -20, 20);
			}
			//renderers attributes
			if (ImGui::CollapsingHeader("Renderers Attributes", m_Renderer_App_Open))
			{
				for (auto iter : m_Renderer)
				{
					if (iter.second)
					{
						ImGui::ColorEdit4("Render Color", &iter.first->GetTransRef().color[0]);
						ImGui::SliderFloat("Scale-x", &iter.first->GetTransRef().scale[0], 0.1f, 2.0f);
						ImGui::SliderFloat("Scale-y", &iter.first->GetTransRef().scale[1], 0.1f, 2.0f);
						ImGui::SliderFloat("Scale-z", &iter.first->GetTransRef().scale[2], 0.1f, 2.0f);
						ImGui::SliderFloat("Scale-xyz", &iter.first->GetTransRef().s_scale, 0.1f, 2.0f);
						ImGui::SliderFloat("metallic", &m_metallic, 0.0f,1.0f);
						ImGui::SliderFloat("roughness", &m_roughness, 0.0f,1.0f);
					}
				}
			}

			//texture
			if (ImGui::CollapsingHeader("Textures", m_Texture_App_Open))
			{
				// albedo texture 
				if (ImGui::Button("Albedo", ImVec2(100.0f,20.0f)))
				{
					m_FileBrowser.Open();
					m_TexturePart.AlbedoTex = true;
				}
				ImGui::SameLine();

				if (ImGui::Checkbox("Use Albedo", &m_EnableTexture.EnableAlbedo))
				{
					 
				}

				for (auto iter : m_Renderer)
				{
					unsigned int tex = 0;
					if (iter.second)
					{
						if (iter.first->GetAlbedoTexture())
						{
							ImGui::Image((void*)(intptr_t)iter.first->GetAlbedoTexture(), ImVec2(100, 100));
						}
						else 
						{
							ImGui::Image((void*)(intptr_t)m_EmptyTexture->GetTexRef(), ImVec2(100, 100));
						}
					}
				}
				

				//ao texture
				if (ImGui::Button("AO",ImVec2(100.0f,20.0f)))
				{
					m_FileBrowser.Open();
					m_TexturePart.AOTex = true;
				}
				ImGui::SameLine();
				if (ImGui::Checkbox("Use AO", &m_EnableTexture.EnableAO))
				{
				}

				for (auto iter : m_Renderer)
				{
					unsigned int tex = 0;
					if (iter.second)
					{
						if (iter.first->GetAOTexture())
						{
							ImGui::Image((void*)(intptr_t)iter.first->GetAOTexture(), ImVec2(100, 100));
						}
						else
						{
							ImGui::Image((void*)(intptr_t)m_EmptyTexture->GetTexRef(), ImVec2(100, 100));
						}
					}
				}
				//metallic texture
				if (ImGui::Button("Metallic", ImVec2(100.0f, 20.0f)))
				{
					m_FileBrowser.Open();
					m_TexturePart.MetallicTex = true;
				}
				ImGui::SameLine();
				if (ImGui::Checkbox("Use Metallic", &m_EnableTexture.EnableMetallic))
				{

				}
				for (auto iter : m_Renderer)
				{
					unsigned int tex = 0;
					if (iter.second)
					{
						if (iter.first->GetMetallicTexture())
						{
							ImGui::Image((void*)(intptr_t)iter.first->GetMetallicTexture(), ImVec2(100, 100));
						}
						else
						{
							ImGui::Image((void*)(intptr_t)m_EmptyTexture->GetTexRef(), ImVec2(100, 100));
						}
					}
				}
				//normal texture
				if (ImGui::Button("Normal", ImVec2(100.0f, 20.0f)))
				{
					m_FileBrowser.Open();
					m_TexturePart.NormalTex = true;
				}
				ImGui::SameLine();
				if (ImGui::Checkbox("Use Normal", &m_EnableTexture.EnableNormal))
				{
				}
				for (auto iter : m_Renderer)
				{
					unsigned int tex = 0;
					if (iter.second)
					{
						if (iter.first->GetNormalTexture())
						{
							ImGui::Image((void*)(intptr_t)iter.first->GetNormalTexture(), ImVec2(100, 100));
						}
						else
						{
							ImGui::Image((void*)(intptr_t)m_EmptyTexture->GetTexRef(), ImVec2(100, 100));
						}
					}
				}
			
				//roughness texture
				if (ImGui::Button("Roughness", ImVec2(100.0f, 20.0f)))
				{
					m_FileBrowser.Open();
					m_TexturePart.RoughnessTex = true;
				}
				ImGui::SameLine();
				if (ImGui::Checkbox("Use Roughness", &m_EnableTexture.EnableRoughness))
				{

				}
				for (auto iter : m_Renderer)
				{
					unsigned int tex = 0;
					if (iter.second)
					{
						if (iter.first->GetRoughnessTexture())
						{
							ImGui::Image((void*)(intptr_t)iter.first->GetRoughnessTexture(), ImVec2(100, 100));
						}
						else
						{
							ImGui::Image((void*)(intptr_t)m_EmptyTexture->GetTexRef(), ImVec2(100, 100));
						}
					}
				}
				std::string textureName = "none";
				textureName = m_FileBrowser.GetSelected().string();

				m_FileBrowser.Display();

				if (m_TexturePart.AlbedoTex)
				{
					for (auto iter : m_Renderer)
					{
						if (iter.second && !m_FileBrowser.IsOpened())
						{
							iter.first->SetAlbedoTex(textureName);
							m_TexturePart.AlbedoTex = false;
						}
					}
				}
				
				for (auto iter : m_Renderer)
				{
					if (iter.second)
					{
						if (m_EnableTexture.EnableAlbedo)
						{
							iter.first->EnableAlbedoTexture();
						}
						else
						{
							iter.first->DisableAlbedoTexture();
						}
					}
				}
				
				if (m_TexturePart.AOTex)
				{
					for (auto iter : m_Renderer)
					{
						if (iter.second && !m_FileBrowser.IsOpened())
						{
							iter.first->SetAOTex(textureName);
							m_TexturePart.AOTex = false;
						}
					}
				}
				for (auto iter : m_Renderer)
				{
					if (iter.second)
					{
						if (m_EnableTexture.EnableAO)
						{
							iter.first->EnableAOTexture();
						}
						else
						{
							iter.first->DisableAOTexture();
						}
					}
				}

				
				if (m_TexturePart.MetallicTex)
				{
					for (auto iter : m_Renderer)
					{
						if (iter.second && !m_FileBrowser.IsOpened())
						{
							iter.first->SetMetallicTex(textureName);
							m_TexturePart.MetallicTex = false;
						}
					}
				}
				for (auto iter : m_Renderer)
				{
					if (iter.second)
					{
						if (m_EnableTexture.EnableMetallic)
						{
							iter.first->EnableMetallicTexture();
						}
						else
						{
							iter.first->DisableMetallicTexture();
						}
					}
				}

			
				if (m_TexturePart.NormalTex)
				{
					for (auto iter : m_Renderer)
					{
						if (iter.second && !m_FileBrowser.IsOpened())
						{
							iter.first->SetNormalTex(textureName);
							m_TexturePart.NormalTex = false;
						}
					}
				}
				for (auto iter : m_Renderer)
				{
					if (iter.second)
					{
						if (m_EnableTexture.EnableNormal)
						{
							iter.first->EnableNormalTexture();
						}
						else
						{
							iter.first->DisableNormalTexture();
						}
					}
				}

			
				if (m_TexturePart.RoughnessTex)
				{
					for (auto iter : m_Renderer)
					{
						if (iter.second && !m_FileBrowser.IsOpened())
						{
							iter.first->SetRoughnessTex(textureName);
							m_TexturePart.RoughnessTex = false;
						}
					}
				}
				for (auto iter : m_Renderer)
				{
					if (iter.second)
					{
						if (m_EnableTexture.EnableRoughness)
						{
							iter.first->EnableRoughnessTexture();
						}
						else
						{
							iter.first->DisableRoughnessTexture();
						}
					}
				}

			}

			//other attributes
			if (ImGui::CollapsingHeader("Other Attributes", m_Other_Attrib_App_Open))
			{
				ImGui::SliderFloat("gamma value", &m_gamma_value, 0.3f, 10.0f);
				if (ImGui::Checkbox("Open MSAA", &m_Open_MSAA))
				{
					if (m_Open_MSAA)
					{
						glEnable(GL_MULTISAMPLE);
					}
				}

				if (ImGui::Checkbox("environment mapping", &EnvirMapping))
				{
				}

				float m_HDR = 0.4f;
				if (ImGui::SliderFloat("HDR", &m_HDR, 0.0f, 10.0f))
				{

				}

			}

		}

		void RenderLayer::CameraSetting(const WinData& windata, entity::FPSCamera* camera)
		{
			//iter is the iterator of renderers, iter.first is the pointer of a Renderer while iter.second is to distinguish
			//wheather it should be rendered
			for (auto iter : m_Renderer)
			{
				if (iter.second == true)
				{
					if (m_CameraPart.fpsCamera)
					{
						glfwSetInputMode(windata.glWindowPtr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
						camera->EnableObject();
						iter.first->GetTransRef().view = camera->GetViewMatrix();
						iter.first->GetTransRef().projection = glm::perspective
						(
							glm::radians(camera->GetCameraAttrib().Zoom),
							(float)windata.win_Width / (float)windata.win_Height,
							0.1f, 100.0f
						);

						auto keyboard = utils::Keyboard::GetKeyboardInstance();
						if (keyboard->GetKeyCode(utils::Keys::RX_KEY_ESCAPE))
						{
							m_CameraPart.fpsCamera = false;
							m_CameraPart.NoCamera = true;
							m_CameraPart.MayaCamera = false;
						}
					}
					if(m_CameraPart.MayaCamera)
					{
						glfwSetInputMode(windata.glWindowPtr, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
						iter.first->GetTransRef().view = camera->GetViewMatrix();
						iter.first->GetTransRef().projection = glm::perspective
						(
							glm::radians(45.0f),
							(float)windata.win_Width / (float)windata.win_Height,
							0.1f, 100.0f
						);
						
					}
					if(m_CameraPart.NoCamera)
					{
						glfwSetInputMode(windata.glWindowPtr, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
						iter.first->GetTransRef().view = camera->GetViewMatrix();
						iter.first->GetTransRef().projection = glm::perspective
						(
							glm::radians(45.0f),
							(float)windata.win_Width / (float)windata.win_Height,
							0.1f, 100.0f
						);

					}
				}
			}

			for (auto iter : m_Flatboards)
			{
				if (m_CameraPart.fpsCamera)
				{
					glfwSetInputMode(windata.glWindowPtr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
					camera->EnableObject();
					iter->GetTransRef().view = camera->GetViewMatrix();
					iter->GetTransRef().projection = glm::perspective
					(
						glm::radians(camera->GetCameraAttrib().Zoom),
						(float)windata.win_Width / (float)windata.win_Height,
						0.1f, 100.0f
					);
			
					auto keyboard = utils::Keyboard::GetKeyboardInstance();
					if (keyboard->GetKeyCode(utils::Keys::RX_KEY_ESCAPE))
					{
						m_CameraPart.fpsCamera = false;
						m_CameraPart.NoCamera = true;
						m_CameraPart.MayaCamera = false;
					}
				}
				if (m_CameraPart.MayaCamera)
				{
					glfwSetInputMode(windata.glWindowPtr, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
					iter->GetTransRef().view = camera->GetViewMatrix();
					iter->GetTransRef().projection = glm::perspective
					(
						glm::radians(45.0f),
						(float)windata.win_Width / (float)windata.win_Height,
						0.1f, 100.0f
					);
				}
				if (m_CameraPart.NoCamera)
				{
					glfwSetInputMode(windata.glWindowPtr, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
					iter->GetTransRef().view = camera->GetViewMatrix();
					iter->GetTransRef().projection = glm::perspective
					(
						glm::radians(45.0f),
						(float)windata.win_Width / (float)windata.win_Height,
						0.1f, 100.0f
					);
			
				}
			}
		}


		void RenderLayer::DefaultCamSet(const WinData& windata, CamPair campair)
		{
			for (auto iter : m_Renderer)
			{
				if (iter.second == true)
				{
					if (m_CameraPart.MayaCamera || m_CameraPart.fpsCamera)
					{
						if (m_CameraPart.MayaCamera)
						{
							glfwSetInputMode(windata.glWindowPtr, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
							campair.second->EnableObject();
							iter.first->GetTransRef().view = campair.second->GetViewMatrix();
							iter.first->GetTransRef().projection = glm::perspective
							(
								glm::radians(campair.second->GetCameraAttrib().Zoom),
								(float)windata.win_Width / (float)windata.win_Height,
								0.1f, 100.0f
							);
							auto keyboard = utils::Keyboard::GetKeyboardInstance();
							if (keyboard->GetKeyCode(utils::Keys::RX_KEY_ESCAPE))
							{
								m_CameraPart.fpsCamera = false;
								m_CameraPart.NoCamera = true;
								m_CameraPart.MayaCamera = false;
							}
						}
						else if (m_CameraPart.fpsCamera)
						{
							glfwSetInputMode(windata.glWindowPtr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
							campair.first->EnableObject();
							iter.first->GetTransRef().view = campair.first->GetViewMatrix();
							iter.first->GetTransRef().projection = glm::perspective
							(
								glm::radians(campair.first->GetCameraAttrib().Zoom),
								(float)windata.win_Width / (float)windata.win_Height,
								0.1f, 100.0f
							);
							auto keyboard = utils::Keyboard::GetKeyboardInstance();
							if (keyboard->GetKeyCode(utils::Keys::RX_KEY_ESCAPE))
							{
								m_CameraPart.fpsCamera = false;
								m_CameraPart.NoCamera = true;
								m_CameraPart.MayaCamera = false;
							}
						}
					}
					if (m_CameraPart.NoCamera)
					{
						glfwSetInputMode(windata.glWindowPtr, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
						iter.first->GetTransRef().view = campair.second->GetViewMatrix();
						iter.first->GetTransRef().projection = glm::perspective
						(
							glm::radians(45.0f),
							(float)windata.win_Width / (float)windata.win_Height,
							0.1f, 100.0f
						);

					}
				}
			}

			for (auto iter : m_Flatboards)
			{
				if (m_CameraPart.fpsCamera || m_CameraPart.MayaCamera)
				{
					if (m_CameraPart.fpsCamera)
					{
						glfwSetInputMode(windata.glWindowPtr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
						campair.first->EnableObject();
						iter->GetTransRef().view = campair.first->GetViewMatrix();
						iter->GetTransRef().projection = glm::perspective
						(
							glm::radians(campair.first->GetCameraAttrib().Zoom),
							(float)windata.win_Width / (float)windata.win_Height,
							0.1f, 100.0f
						);
					}
					else if(m_CameraPart.MayaCamera)
					{
						glfwSetInputMode(windata.glWindowPtr, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
						campair.second->EnableObject();
						iter->GetTransRef().view = campair.second->GetViewMatrix();
						iter->GetTransRef().projection = glm::perspective
						(
							glm::radians(campair.second->GetCameraAttrib().Zoom),
							(float)windata.win_Width / (float)windata.win_Height,
							0.1f, 100.0f
						);
					}
					

					auto keyboard = utils::Keyboard::GetKeyboardInstance();
					if (keyboard->GetKeyCode(utils::Keys::RX_KEY_ESCAPE))
					{
						m_CameraPart.fpsCamera = false;
						m_CameraPart.NoCamera = true;
						m_CameraPart.MayaCamera = false;
					}
				}
				if (m_CameraPart.NoCamera)
				{
					glfwSetInputMode(windata.glWindowPtr, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
					iter->GetTransRef().view = campair.second->GetViewMatrix();
					iter->GetTransRef().projection = glm::perspective
					(
						glm::radians(45.0f),
						(float)windata.win_Width / (float)windata.win_Height,
						0.1f, 100.0f
					);

				}
			}
		}

		void RenderLayer::File()
		{
			//if (ImGui::Button("Openfile"))
			//{
			//	m_FileBrowser.Open();
			//}
			//
			//m_FileBrowser.Display();

			
			
			
		}

		void RenderLayer::LightModel(RenderLight* light, entity::FPSCamera* camera)
		{
			for (auto iter : m_Renderer)
			{
				if (iter.second)
				{
					iter.first->GetRenderDataRef()->m_Shader->SetVec4("u_color", iter.first->GetTransRef().color);
					iter.first->GetRenderDataRef()->m_Shader->SetVec3("u_lightColor", light->GetLightColor());
					iter.first->GetRenderDataRef()->m_Shader->SetVec3("u_lightPos", light->GetLightPosition());
					iter.first->GetRenderDataRef()->m_Shader->SetVec3("u_viewPos", camera->GetCameraAttrib().Position);
					iter.first->GetRenderDataRef()->m_Shader->SetFloat("u_Shineness", light->GetShineness());
					iter.first->GetRenderDataRef()->m_Shader->SetBool("u_open_phong", m_LightModelPart.PhongModel);
					iter.first->GetRenderDataRef()->m_Shader->SetBool("u_blinn_phong", m_LightModelPart.Blinn_Phong);
					iter.first->GetRenderDataRef()->m_Shader->SetFloat("u_gamma_value", m_gamma_value);
					iter.first->GetRenderDataRef()->m_Shader->SetBool("u_light_pbr", m_LightModelPart.LightPBR);
					iter.first->GetRenderDataRef()->m_Shader->SetBool("u_texture_pbr", m_LightModelPart.TexturePBR);
					iter.first->GetRenderDataRef()->m_Shader->SetFloat("u_metallic", m_metallic);
					iter.first->GetRenderDataRef()->m_Shader->SetFloat("u_roughness", m_roughness);
					iter.first->UnbindObject();
				}
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


		void RenderLayer::DefSkybox(const WinData& windata, entity::MayaCamera* camera)
		{

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
