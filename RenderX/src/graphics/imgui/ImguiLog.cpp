#include "graphics/imgui/ImguiLog.h"

namespace renderx {
	namespace graphics {

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