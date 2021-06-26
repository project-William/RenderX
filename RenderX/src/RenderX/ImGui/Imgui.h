#pragma once

namespace renderx::ui
{
	class Imgui
	{
	public:
		static void ImguiSetup();

		static void ImguiBegin();
		static void DockSpace();
		
		static void ImguiEnd();
		
		static void ImguiDestroy();

		static void Run();

		static void ApplyImguiStyle();
	};
}