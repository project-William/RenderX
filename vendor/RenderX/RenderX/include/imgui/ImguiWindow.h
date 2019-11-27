#pragma once
#include "..//..//Common.h"

namespace renderx::ui
{

	class REN_API ImguiWindow
	{
	public:
		ImguiWindow();
		virtual ~ImguiWindow() {}

		static void UIBegin();
		static void UISetup();
		static void UIEnd();

		virtual void DisplayWindow();
		virtual void OnDetach();


	};
}