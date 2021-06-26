#pragma once
#include "pch.h"
#include "../Core/Framebuffer.h"
#include "../Core/Hdr.h"

namespace renderx::ui
{
	class ViewportWindow
	{
	public:
		static std::shared_ptr<ViewportWindow>& Get();
		~ViewportWindow();

			
		void RunViewportWindow(Core::FrameBuffer& framebuffer);

		glm::vec2 GetViewportSize() { return m_ViewportSize; }
		glm::vec2 GetWindowPos() { return m_ViewportPos; }
	private:
		ViewportWindow();

		static std::shared_ptr<ViewportWindow> s_Instance;
		glm::vec2 m_ViewportSize;
		glm::vec2 m_ViewportPos;

		glm::vec3 lastTranslation = glm::vec3(0.0f);


	};
}