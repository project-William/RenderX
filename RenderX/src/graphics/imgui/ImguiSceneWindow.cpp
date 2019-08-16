#include "graphics/imgui/ImguiSceneWindow.h"

namespace renderx {
	namespace ui {



		ImguiSceneWindow::ImguiSceneWindow()
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
			
		}

	}
}