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
		}

		void ImguiLog::Log()
		{
			ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
			ImGui::Begin("Example: Log", &p_open);
			static int counter = 0;
			for (int n = 0; n < 1; n++)
			{
				const char* categories[3] = { "info", "warn", "error" };
				const char* words[] = { "Bumfuzzled", "Cattywampus", "Snickersnee", "Abibliophobia", "Absquatulate", "Nincompoop", "Pauciloquent" };
				m_AppLog.AddLog("[%05d] [%s] Hello, current time is %.1f, here's a word: '%s'\n",
					ImGui::GetFrameCount(), categories[counter % IM_ARRAYSIZE(categories)], ImGui::GetTime(), words[counter % IM_ARRAYSIZE(words)]);
				counter++;
			}
			ImGui::End();

			// Actually call in the regular Log helper (which will Begin() into the same window as we just did)
			m_AppLog.Draw("Example: Log", &p_open);

		}

		void ImguiLog::EndLog()
		{
		}

		


	}
}