#include "graphics/imgui/ImguiSetWindow.h"

namespace renderx {
	namespace ui {

		ImguiSetWindow::ImguiSetWindow()
		{

		}

		ImguiSetWindow::~ImguiSetWindow()
		{

		}

		void ImguiSetWindow::BeginSetWindow()
		{
			DockSpace(m_DockSpace_Open);
			ImGui::Begin("Graphics Settings");
		}

		void ImguiSetWindow::GraphicsSettingWindow()
		{
			{
				ImGui::Checkbox("DockSpace", &m_DockSpace_Open);
			}
		}

		void ImguiSetWindow::CameraSetting(const graphics::WinData& windata, CamPair& campair, graphics::RenderLayer& layer)
		{
			CameraHeader(layer);
			SkyboxHeader(layer);
			RendererHeader(layer);
			LightModelHeader(layer);
			TextureHeader(layer);
		}

		void ImguiSetWindow::CameraHeader(graphics::RenderLayer& layer)
		{
			if (ImGui::CollapsingHeader("Camera"))
			{
				if (ImGui::Checkbox("FPS Game Camera", &layer.IsCameraRef().fpsCamera))
				{
					SINGLE_CHOICE_IN_TWO(layer.IsCameraRef().fpsCamera, layer.IsCameraRef().MayaCamera);
				}

				if (ImGui::Checkbox("Default Camera", &layer.IsCameraRef().MayaCamera))
				{
					SINGLE_CHOICE_IN_TWO(layer.IsCameraRef().MayaCamera, layer.IsCameraRef().fpsCamera);
				}
			}
		}

		void ImguiSetWindow::SkyboxHeader(graphics::RenderLayer& layer)
		{

			if (ImGui::CollapsingHeader("Skybox"))
			{
				if (ImGui::Checkbox("Skybox 1", &layer.IsSkyboxRenderRef().skybox_1))
				{
					SINGLE_CHOICE_IN_FOUR(layer.IsSkyboxRenderRef().skybox_1, 
						layer.IsSkyboxRenderRef().skybox_2, 
						layer.IsSkyboxRenderRef().skybox_3, 
						layer.IsSkyboxRenderRef().skybox_4);
				}

				if (ImGui::Checkbox("Skybox 2", &layer.IsSkyboxRenderRef().skybox_2))
				{
					SINGLE_CHOICE_IN_FOUR(layer.IsSkyboxRenderRef().skybox_2,
						layer.IsSkyboxRenderRef().skybox_1,
						layer.IsSkyboxRenderRef().skybox_3,
						layer.IsSkyboxRenderRef().skybox_4);
				}

				if (ImGui::Checkbox("Skybox 3", &layer.IsSkyboxRenderRef().skybox_3))
				{
					SINGLE_CHOICE_IN_FOUR(layer.IsSkyboxRenderRef().skybox_3,
						layer.IsSkyboxRenderRef().skybox_1,
						layer.IsSkyboxRenderRef().skybox_2,
						layer.IsSkyboxRenderRef().skybox_4);
				}

				if (ImGui::Checkbox("Skybox 4", &layer.IsSkyboxRenderRef().skybox_4))
				{
					SINGLE_CHOICE_IN_FOUR(layer.IsSkyboxRenderRef().skybox_4,
						layer.IsSkyboxRenderRef().skybox_1,
						layer.IsSkyboxRenderRef().skybox_3,
						layer.IsSkyboxRenderRef().skybox_2);
				}
			}
		}

		void ImguiSetWindow::RendererHeader(graphics::RenderLayer& layer)
		{
			auto rendererID = layer.GetRenderersRef().begin();
			

			if (ImGui::CollapsingHeader("Renderers", m_Renderer_App_Open))
			{

				if (ImGui::Checkbox("Sphere", &layer.IsRenderRef().renderer_1))
				{
					SINGLE_CHOICE_IN_FOUR(layer.IsRenderRef().renderer_1,
						layer.IsRenderRef().renderer_2, 
						layer.IsRenderRef().renderer_3, 
						layer.IsRenderRef().renderer_4);
					for (auto& renderer : layer.GetRenderersRef())
					{
						renderer.second = false;
					}
					rendererID->second = layer.IsRenderRef().renderer_1;
				}

				if (ImGui::Checkbox("cube", &layer.IsRenderRef().renderer_2))
				{
					SINGLE_CHOICE_IN_FOUR(layer.IsRenderRef().renderer_2,
						layer.IsRenderRef().renderer_1,
						layer.IsRenderRef().renderer_3,
						layer.IsRenderRef().renderer_4);
					for (auto& renderer : layer.GetRenderersRef())
					{
						renderer.second = false;
					}
					(++rendererID)->second = layer.IsRenderRef().renderer_2;
				}

				if (ImGui::Checkbox("Model_1", &layer.IsRenderRef().renderer_3))
				{
				}

				if (ImGui::Checkbox("Model_2", &layer.IsRenderRef().renderer_4))
				{
				}
			}
		}

		void ImguiSetWindow::LightModelHeader(graphics::RenderLayer& layer)
		{
			if (ImGui::CollapsingHeader("Light Model", m_LightModel_Open))
			{
				if (ImGui::Checkbox("Blinn Phong", &layer.IsLightModeRef().Blinn_Phong))
				{
					SINGLE_CHOICE_IN_THREE(layer.IsLightModeRef().Blinn_Phong,
						layer.IsLightModeRef().LightPBR, 
						layer.IsLightModeRef().TexturePBR);
				}

				if (ImGui::Checkbox("Lighting PBR", &layer.IsLightModeRef().LightPBR))
				{
					SINGLE_CHOICE_IN_THREE(layer.IsLightModeRef().LightPBR,
						layer.IsLightModeRef().Blinn_Phong,
						layer.IsLightModeRef().TexturePBR);
				}

				if (ImGui::Checkbox("Texture PBR", &layer.IsLightModeRef().TexturePBR))
				{
					SINGLE_CHOICE_IN_THREE(layer.IsLightModeRef().TexturePBR,
						layer.IsLightModeRef().Blinn_Phong,
						layer.IsLightModeRef().LightPBR);
				}

				//ImGui::SliderFloat("Shineness", &light->GetShinenessRef(), 0.0f, 128.0f);
				//ImGui::ColorEdit3("Light Color", &light->GetLightColorRef()[0]);
				//ImGui::SliderFloat("X-axis", &light->GetLightPositionRef().x, -20, 20);
				//ImGui::SliderFloat("Y-axis", &light->GetLightPositionRef().y, -20, 20);
				//ImGui::SliderFloat("Z-axis", &light->GetLightPositionRef().z, -20, 20);
			}
		}

		void ImguiSetWindow::TextureHeader(graphics::RenderLayer& layer)
		{
			auto& texturePart = layer.IsTextureRef();
			auto& enableTexture = layer.IsEnableTextureRef();
			auto& renderers = layer.GetRenderersRef();
			//texture
			if (ImGui::CollapsingHeader("Textures", m_Texture_App_Open))
			{
				// albedo texture 
				if (ImGui::Button("ALBEDO", ImVec2(100.0f, 20.0f)))
				{
					m_FileBrowser.Open();
					texturePart.AlbedoTex = true;
				}
				ImGui::SameLine();
				if (ImGui::Checkbox("USE ALBEDO", &enableTexture.EnableAlbedo))
				{

				}

				for (auto iter : layer.GetRenderersRef())
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
							ImGui::Image((void*)(intptr_t)layer.GetEmptyTextureRef()->GetTexRef(), ImVec2(100, 100));
						}
					}
				}


				//ao texture
				if (ImGui::Button("AO", ImVec2(100.0f, 20.0f)))
				{
					m_FileBrowser.Open();
					texturePart.AOTex = true;
				}
				ImGui::SameLine();
				if (ImGui::Checkbox("USE AO", &enableTexture.EnableAO))
				{

				}

				for (auto iter : renderers)
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
							ImGui::Image((void*)(intptr_t)layer.GetEmptyTextureRef()->GetTexRef(), ImVec2(100, 100));
						}
					}
				}
				//metallic texture
				if (ImGui::Button("METALLIC", ImVec2(100.0f, 20.0f)))
				{
					m_FileBrowser.Open();
					texturePart.MetallicTex = true;
				}
				ImGui::SameLine();
				if (ImGui::Checkbox("USE METALLIC", &enableTexture.EnableMetallic))
				{

				}

				for (auto iter : renderers)
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
							ImGui::Image((void*)(intptr_t)layer.GetEmptyTextureRef()->GetTexRef(), ImVec2(100, 100));
						}
					}
				}
				//normal texture
				if (ImGui::Button("NORMAL", ImVec2(100.0f, 20.0f)))
				{
					m_FileBrowser.Open();
					texturePart.NormalTex = true;
				}
				ImGui::SameLine();
				if (ImGui::Checkbox("USE NORMAL", &enableTexture.EnableNormal))
				{

				}
				for (auto iter : renderers)
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
							ImGui::Image((void*)(intptr_t)layer.GetEmptyTextureRef()->GetTexRef(), ImVec2(100, 100));
						}
					}
				}

				//roughness texture
				if (ImGui::Button("ROUGHNESS", ImVec2(100.0f, 20.0f)))
				{
					m_FileBrowser.Open();
					texturePart.RoughnessTex = true;
				}
				ImGui::SameLine();
				if (ImGui::Checkbox("USE ROUGHNESS", &enableTexture.EnableRoughness))
				{

				}

				for (auto iter : renderers)
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
							ImGui::Image((void*)(intptr_t)layer.GetEmptyTextureRef()->GetTexRef(), ImVec2(100, 100));
						}
					}
				}
				std::string textureName = "none";
				textureName = m_FileBrowser.GetSelected().string();

				m_FileBrowser.Display();

				if (texturePart.AlbedoTex)
				{
					for (auto iter : renderers)
					{
						if (iter.second && !m_FileBrowser.IsOpened())
						{
							iter.first->SetAlbedoTex(textureName);
							texturePart.AlbedoTex = false;
						}
					}
				}

				for (auto iter : renderers)
				{
					if (iter.second)
					{
						if (enableTexture.EnableAlbedo)
						{
							iter.first->EnableAlbedoTexture();
						}
						else
						{
							iter.first->DisableAlbedoTexture();
						}
					}
				}

				if (texturePart.AOTex)
				{
					for (auto iter : renderers)
					{
						if (iter.second && !m_FileBrowser.IsOpened())
						{
							iter.first->SetAOTex(textureName);
							texturePart.AOTex = false;
						}
					}
				}
				for (auto iter : renderers)
				{
					if (iter.second)
					{
						if (enableTexture.EnableAO)
						{
							iter.first->EnableAOTexture();
						}
						else
						{
							iter.first->DisableAOTexture();
						}
					}
				}


				if (texturePart.MetallicTex)
				{
					for (auto iter : renderers)
					{
						if (iter.second && !m_FileBrowser.IsOpened())
						{
							iter.first->SetMetallicTex(textureName);
							texturePart.MetallicTex = false;
						}
					}
				}
				for (auto iter : renderers)
				{
					if (iter.second)
					{
						if (enableTexture.EnableMetallic)
						{
							iter.first->EnableMetallicTexture();
						}
						else
						{
							iter.first->DisableMetallicTexture();
						}
					}
				}


				if (texturePart.NormalTex)
				{
					for (auto iter : renderers)
					{
						if (iter.second && !m_FileBrowser.IsOpened())
						{
							iter.first->SetNormalTex(textureName);
							texturePart.NormalTex = false;
						}
					}
				}
				for (auto iter : renderers)
				{
					if (iter.second)
					{
						if (enableTexture.EnableNormal)
						{
							iter.first->EnableNormalTexture();
						}
						else
						{
							iter.first->DisableNormalTexture();
						}
					}
				}


				if (texturePart.RoughnessTex)
				{
					for (auto iter : renderers)
					{
						if (iter.second && !m_FileBrowser.IsOpened())
						{
							iter.first->SetRoughnessTex(textureName);
							texturePart.RoughnessTex = false;
						}
					}
				}
				for (auto iter : renderers)
				{
					if (iter.second)
					{
						if (enableTexture.EnableRoughness)
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
		}

		void ImguiSetWindow::OtherAttribHeader()
		{
		}

	


		void ImguiSetWindow::EndSetWindow()
		{
			ImGui::End();
		}

		void ImguiSetWindow::DockSpace(bool& dockopen)
		{
			if (dockopen)
			{
				static bool opt_fullscreen_persistant = true;
				bool opt_fullscreen = opt_fullscreen_persistant;
				static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

				// because it would be confusing to have two docking targets within each others.
				ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
				if (opt_fullscreen)
				{
					ImGuiViewport* viewport = ImGui::GetMainViewport();
					ImGui::SetNextWindowPos(viewport->Pos);
					ImGui::SetNextWindowSize(viewport->Size);
					ImGui::SetNextWindowViewport(viewport->ID);
					ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
					ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
					window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
					window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
				}

				// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
				if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
					window_flags |= ImGuiWindowFlags_NoBackground;

				// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
				// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
				// all active windows docked into it will lose their parent and become undocked.
				// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
				// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
				ImGui::Begin("DockSpace Demo", &dockopen, window_flags);
				ImGui::PopStyleVar();

				if (opt_fullscreen)
					ImGui::PopStyleVar(2);

				// DockSpace
				ImGuiIO& io = ImGui::GetIO();
				if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
				{
					ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
					ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
				}

				if (ImGui::BeginMenuBar())
				{
					if (ImGui::BeginMenu("Docking"))
					{

						if (ImGui::MenuItem("Flag: NoSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0))                 dockspace_flags ^= ImGuiDockNodeFlags_NoSplit;
						if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0))                dockspace_flags ^= ImGuiDockNodeFlags_NoResize;
						if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0))  dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode;
						if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0))     dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode;
						if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0))          dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar;
						ImGui::Separator();
						if (ImGui::MenuItem("Close DockSpace", NULL, false, dockopen != NULL))
							dockopen = false;
						ImGui::EndMenu();
					}

					ImGui::EndMenuBar();
				}

				ImGui::End();
			}
		}
	}
}