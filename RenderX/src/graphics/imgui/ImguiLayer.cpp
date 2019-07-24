#include "graphics/imgui/ImguiLayer.h"


namespace renderx {
	namespace graphics {

		ImguiLayer::ImguiLayer()
		{

		}

		ImguiLayer::ImguiLayer(GLFWwindow* window, WinData winData)
			:m_WinData(winData),m_Window(window)
		{
			
		}


		ImguiLayer::~ImguiLayer()
		{

		}

		void ImguiLayer::SetUpImguiLayer()
		{
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
			//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
			io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
			io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
			//io.ConfigViewportsNoAutoMerge = true;
			//io.ConfigViewportsNoTaskBarIcon = true;

			// Setup Dear ImGui style
			//ImGui::StyleColorsDark();
			ImGui::StyleColorsLight();
			//ImGui::StyleColorsClassic();

			// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
			ImGuiStyle& style = ImGui::GetStyle();
			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				style.WindowRounding = 0.0f;
				style.Colors[ImGuiCol_WindowBg].w = 1.0f;
			}

			// Setup Platform/Renderer bindings
			ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
			ImGui_ImplOpenGL3_Init("#version 410");
		}


		void ImguiLayer::OnAttach()
		{
			SetUpImguiLayer();
		}

		void ImguiLayer::OnDetach()
		{
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();
		}


		void ImguiLayer::OnImguiLayer()
		{
			ShowDemo();
		}

		void ImguiLayer::Begin()
		{
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
		}
		
		void ImguiLayer::ShowDemo()
		{
			bool show_demo_window = true;
			if (show_demo_window)
				ImGui::ShowDemoWindow(&show_demo_window);
		}
		
		void ImguiLayer::ImguiWindow()
		{
			ImGuiWindowFlags window_flags = false;
			glm::vec4 vec4;
			bool show = false;
			ImGui::Begin("Graphics Settings");
			ImGui::ColorEdit4("objectcolor", &vec4[0]);



			ImGui::End();
		}


		void ImguiLayer::SettingWindowBegin()
		{
			ImGui::Begin("Graphics Settings");
		}


		void ImguiLayer::SettingWindowEnd()
		{
			ImGui::End();
		}

		void ImguiLayer::End()
		{
			ImGuiIO& io = ImGui::GetIO();
			io.DisplaySize = ImVec2((float)m_WinData.win_Width, (float)m_WinData.win_Height);


			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				GLFWwindow* backup_current_context = glfwGetCurrentContext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				glfwMakeContextCurrent(backup_current_context);
			}
		}
	}
}