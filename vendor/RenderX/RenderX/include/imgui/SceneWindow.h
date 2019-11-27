#pragma once
#include "ImguiWindow.h"

namespace renderx::ui
{

	class REN_API SceneWindow
	{
	public:
		SceneWindow();
		~SceneWindow();

		static void Begin();
		static void End();

		uint32_t GetWidth()const { return m_Width; }
		uint32_t GetHeight()const { return m_Height; }

		void SceneViewport();
	private:
		uint32_t m_Width;
		uint32_t m_Height;
	};

}