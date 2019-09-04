#include "graphics/imgui/ImguiSceneWindow.h"

namespace renderx {
	namespace ui {

		std::shared_ptr<ImguiSceneWindow> ImguiSceneWindow::m_Instance = nullptr;

		std::shared_ptr<ImguiSceneWindow> ImguiSceneWindow::Create()
		{
			if (!m_Instance)
			{
				m_Instance = std::shared_ptr<ImguiSceneWindow>(new ImguiSceneWindow());
				return m_Instance;
			}
			return m_Instance;
		}

		ImguiSceneWindow::ImguiSceneWindow()
			:m_SceneWinHeight(0),m_SceneWinWidth(0)
		{

		}

		ImguiSceneWindow::~ImguiSceneWindow()
		{

		}

		void ImguiSceneWindow::BeginSceneWindow()
		{
			ImGui::Begin("Renderx Viewport");
		}

		void ImguiSceneWindow::EndSceneWindow()
		{
			ImGui::End();
		}

		void ImguiSceneWindow::SceneWindow(const graphics::WinData& windata, 
										   const GLuint& texture)
		{
			
			ImVec2 pos = ImGui::GetCursorScreenPos();
			ImGui::GetWindowDrawList()->AddImage((void*)texture,
				ImVec2(pos.x, pos.y),
				ImVec2(pos.x + ImGui::GetWindowWidth(), pos.y + ImGui::GetWindowHeight()),
				ImVec2(0, 1), ImVec2(1, 0));
			m_SceneWinWidth = ImGui::GetWindowWidth();
			m_SceneWinHeight = ImGui::GetWindowHeight();
		}

	}
}