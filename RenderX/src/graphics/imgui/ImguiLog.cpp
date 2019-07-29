#include "graphics/imgui/ImguiLog.h"

namespace renderx {
	namespace ui {

		ImguiLog::ImguiLog()
		{

		}

		ImguiLog::~ImguiLog()
		{
		}

		void ImguiLog::BeginLog()
		{
			if (ImGui::Begin("Renderx Log"))
			{

			}
		}

		void ImguiLog::EndLog()
		{
			ImGui::End();
		}

		


	}
}