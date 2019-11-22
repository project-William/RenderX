#include "imgui/SettingWindow.h"
#include "Window.h"
#include "utils/Keyboard.h"

namespace renderx
{
	namespace ui
	{
		SettingWindow::SettingWindow()
		{
			m_TempScene = Scene::GetSceneInstance();
			for (size_t i = 0; i < m_TempScene->GetRenderCount(); i++)
			{
				Boolean choose = { false };
				m_RendererChoose.push_back(choose);
			}
			m_Riterator = m_TempScene->GetRenderListRef().rbegin();
			m_Iterator = m_TempScene->GetRenderListRef().begin();

		}


		SettingWindow::~SettingWindow()
		{

		}

		void SettingWindow::OnUpdate()
		{
			
			
		}

		void SettingWindow::Begin()
		{
			DockSpace();
			m_TempScene = Scene::GetSceneInstance();

			bool open = true;
			ImGui::Begin("FPS", &open);
			{
				ImGui::Checkbox("DockSpace", &m_DockOpen);
			}
			


			
			//ImGui::ShowDemoWindow();

		}

		void SettingWindow::End()
		{
			ImGui::End();
		}

		void SettingWindow::Demo()
		{
			ImGui::ShowDemoWindow();
		}

		void SettingWindow::RendererWindow()
		{
			bool RenderWindowOpen = true;
			
			//count
			std::string countstr = "";

			ImGui::Begin("Renderer", &RenderWindowOpen);
			/*manage renderers*/
			//quad
			ImGui::Text("Quad  "); ImGui::SameLine();
			if (ImGui::Button("Add Q", ImVec2(80, 20)))
			{
				m_TempScene->AddQuadRenderCount();
				Boolean choose = { false };
				m_RendererChoose.push_back(choose);
			}
			ImGui::SameLine();
			if (ImGui::Button("Del Q", ImVec2(80,20)))
			{
				m_TempScene->DelQuadRenderCount();

			}
			ImGui::SameLine(); countstr = "Count:" + std::to_string(m_TempScene->GetQuadRenderCount());ImGui::Text(countstr.c_str());
			//block
			ImGui::Text("Block "); ImGui::SameLine();
			if (ImGui::Button("Add B", ImVec2(80, 20)))
			{
				m_TempScene->AddBlockRenderCount();
				Boolean choose = { false };
				m_RendererChoose.push_back(choose);
			}
			ImGui::SameLine();
			if (ImGui::Button("Del B", ImVec2(80, 20)))
			{
				m_TempScene->DelBlockRenderCount();
			}
			ImGui::SameLine(); countstr = "Count:" + std::to_string(m_TempScene->GetBlockRenderCount()); ImGui::Text(countstr.c_str());
			//sphere
			ImGui::Text("Sphere"); ImGui::SameLine();
			if (ImGui::Button("Add S", ImVec2(80, 20)))
			{
				m_TempScene->AddSphereRenderCount();
				Boolean choose = { false };
				m_RendererChoose.push_back(choose);
			}
			ImGui::SameLine();
			if (ImGui::Button("Del S", ImVec2(80, 20)))
			{
				m_TempScene->DelSphereRenderCount();
			}
			ImGui::SameLine(); countstr = "Count:" + std::to_string(m_TempScene->GetSphereRenderCount()); ImGui::Text(countstr.c_str());
			//model
			ImGui::Text("Model "); ImGui::SameLine();
			if (ImGui::Button("Add M", ImVec2(80, 20)))
			{
				m_TempScene->AddSphereRenderCount();
				Boolean choose = { false };
				m_RendererChoose.push_back(choose);
			}
			ImGui::SameLine();
			if (ImGui::Button("Del M", ImVec2(80, 20)))
			{
				m_TempScene->DelSphereRenderCount();
			}
			ImGui::SameLine(); 
			ImGui::SameLine(); countstr = "Count:" + std::to_string(m_TempScene->GetModelRenderCount()); ImGui::Text(countstr.c_str());
			//renderer list
			ImGui::Separator();
			if (ImGui::TreeNode("Renderer List"))
			{
				auto it = m_RendererChoose.begin();
				for (auto& iter : m_TempScene->GetRenderListRef())
				{
					ImGui::Checkbox((iter.m_Name).c_str(), &iter.m_IsChoose);
				}
				ImGui::TreePop();
			}
			ImGui::End();
		}

		void SettingWindow::AttribWindow(std::shared_ptr<entity::Camera> cam)
		{
			//ImVec4 color;
			bool attrib = true;
			ImGui::Begin("Attribute", &attrib);

			auto keyboard = utils::Keyboard::GetKeyboardInstance();
			glm::vec3 forward = glm::normalize(glm::vec3(
				(glm::vec3(0.0f) - cam->GetCameraAttribRef().Position).x, 
				0.0f, 
				(glm::vec3(0.0f) - cam->GetCameraAttribRef().Position).z
			));
			glm::vec3 up(glm::vec3(0.0f, 1.0f, 0.0f));
			glm::vec3 right = glm::normalize(glm::cross(forward, up));

			ImGui::Text("Movement");

			for (auto& iter : m_TempScene->GetRenderListRef())
			{
				if (iter.m_IsChoose)
				{
					if (keyboard->GetKeyCode(utils::Keys::RX_KEY_W))
					{
						iter.m_ModelMat = glm::translate(iter.m_ModelMat, forward * 0.1f);
					}
					if (keyboard->GetKeyCode(utils::Keys::RX_KEY_A))
					{
						iter.m_ModelMat = glm::translate(iter.m_ModelMat, -right * 0.1f);
					}
					if (keyboard->GetKeyCode(utils::Keys::RX_KEY_S))
					{
						iter.m_ModelMat = glm::translate(iter.m_ModelMat, -forward * 0.1f);
					}
					if (keyboard->GetKeyCode(utils::Keys::RX_KEY_D))
					{
						iter.m_ModelMat = glm::translate(iter.m_ModelMat, right * 0.1f);
					}
					if (keyboard->GetKeyCode(utils::Keys::RX_KEY_LEFT_SHIFT))
					{
						iter.m_ModelMat = glm::translate(iter.m_ModelMat, -up * 0.1f);
					}
					if (keyboard->GetKeyCode(utils::Keys::RX_KEY_SPACE))
					{
						iter.m_ModelMat = glm::translate(iter.m_ModelMat, up * 0.1f);
					}
				}
			}

			if (ImGui::TreeNode("Color/Picker"))
			{
				static bool alpha_preview = true;
				static bool alpha_half_preview = false;
				static bool drag_and_drop = true;
				static bool options_menu = true;
				static bool hdr = false;
				int misc_flags = (hdr ? ImGuiColorEditFlags_HDR : 0) | (drag_and_drop ? 0 : ImGuiColorEditFlags_NoDragDrop) | (alpha_half_preview ? ImGuiColorEditFlags_AlphaPreviewHalf : (alpha_preview ? ImGuiColorEditFlags_AlphaPreview : 0)) | (options_menu ? 0 : ImGuiColorEditFlags_NoOptions);


				ImGui::Text("Color picker:");
				static bool alpha = true;
				static bool alpha_bar = true;
				static bool side_preview = true;
				static bool ref_color = false;
				static ImVec4 ref_color_v(1.0f, 0.0f, 1.0f, 0.5f);
				static int display_mode = 0;
				static int picker_mode = 0;
				ImGui::Checkbox("With Alpha", &alpha);
				ImGui::Checkbox("With Alpha Bar", &alpha_bar);
				ImGui::Checkbox("With Side Preview", &side_preview);
				if (side_preview)
				{
					ImGui::SameLine();
					ImGui::Checkbox("With Ref Color", &ref_color);
				}
				ImGui::Combo("Display Mode", &display_mode, "Auto/Current\0None\0RGB Only\0HSV Only\0Hex Only\0");
				ImGui::Combo("Picker Mode", &picker_mode, "Auto/Current\0Hue bar + SV rect\0Hue wheel + SV triangle\0");
				ImGuiColorEditFlags flags = misc_flags;
				if (!alpha)            flags |= ImGuiColorEditFlags_NoAlpha;        // This is by default if you call ColorPicker3() instead of ColorPicker4()
				if (alpha_bar)         flags |= ImGuiColorEditFlags_AlphaBar;
				if (!side_preview)     flags |= ImGuiColorEditFlags_NoSidePreview;
				if (picker_mode == 1)  flags |= ImGuiColorEditFlags_PickerHueBar;
				if (picker_mode == 2)  flags |= ImGuiColorEditFlags_PickerHueWheel;
				if (display_mode == 1) flags |= ImGuiColorEditFlags_NoInputs;       // Disable all RGB/HSV/Hex displays
				if (display_mode == 2) flags |= ImGuiColorEditFlags_DisplayRGB;     // Override display mode
				if (display_mode == 3) flags |= ImGuiColorEditFlags_DisplayHSV;
				if (display_mode == 4) flags |= ImGuiColorEditFlags_DisplayHex;
				
				for (auto& iter : m_TempScene->GetRenderListRef())
				{
					if(iter.m_IsChoose)
						ImGui::ColorPicker4("MyColor##4", (float*)&iter.m_Albedo, flags, ref_color ? &ref_color_v.x : NULL);
				}
				ImGui::TreePop();
			}

			ImGui::End();
		}

		void SettingWindow::TexturePart()
		{
		}

		void SettingWindow::EnvirPart()
		{
		}


		void SettingWindow::FPSWindow(double duration)
		{
			static bool animate = true;
			bool FPS = true;
			ImGui::Begin("FPS DIAGRAM", &FPS);
			static float values[60] = { 0 };
			static int values_offset = 0;
			static double refresh_time = 0.0;
			if (!animate || refresh_time == 0.0)
				refresh_time = ImGui::GetTime();
			while (refresh_time < ImGui::GetTime()) // Create dummy data at fixed 60 hz rate for the demo
			{
				static float phase = 0.0f;
				values[values_offset] = 1/duration;
				values_offset = (values_offset + 1) % IM_ARRAYSIZE(values);
				//phase += 0.10f * values_offset;
				refresh_time += 1.0f / 60.0f;
			}
			std::string fps = "FPS:" + std::to_string(1 / duration);
			ImGui::PlotLines("", values, IM_ARRAYSIZE(values), values_offset, fps.c_str(), 55.000f, 150.000f, ImVec2(0, 80));
			ImGui::End();
		}

		void SettingWindow::DockSpace()
		{

			if (m_DockOpen)
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
				ImGui::Begin("DockSpace Demo", &m_DockOpen, window_flags);
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
						if (ImGui::MenuItem("Close DockSpace", NULL, false, m_DockOpen != NULL))
							m_DockOpen = false;
						ImGui::EndMenu();
					}
					ImGui::EndMenuBar();
				}
				ImGui::End();
			}
		}


		void SettingWindow::Test()
		{
			bool a = true;
			ImGui::Begin("yes", &a);

			struct BOOL
			{
				bool is;
			};

			std::list<BOOL> list;
			list.push_back({ false });
			
			int i = 0;
			for (auto iter : list)
			{
			}
			

			
			ImGui::End();
		}
	}
}