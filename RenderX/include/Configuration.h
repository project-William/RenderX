#pragma once
#include "Window.h"

#include "event/Event.h"
#include "event/KeyboardEvent.h"
#include "event/MouseEvent.h"
#include "event/WindowEvent.h"

#include "utils/Keyboard.h"
#include "utils/Mouse.h"

namespace renderx
{
	class REN_API Configuration
	{

	public:
		Configuration();
		~Configuration();

		Configuration(const Configuration&) = delete;
		Configuration& operator=(const Configuration&) = delete;

	protected:

		std::shared_ptr<Window> m_Window;
		std::shared_ptr<utils::Keyboard> m_Keyboard;
		std::shared_ptr<utils::Mouse> m_Mouse;

		void OnEvent(events::Event& e);

		bool OnWindowResizedEvent(events::WindowResizedEvent& e);
		bool OnWindowClosedEvent(events::WindowClosedEvent& e);
		bool OnWindowMovedEvent(events::WindowMovedEvent& e);

		bool OnMouseButtonPressed(events::MousePressedEvent& e);
		bool OnMouseButtonReleased(events::MouseRelasedEvent& e);
		bool OnMouseMovedEvent(events::MouseMovedEvent& e);
		bool OnMouseScrollEvent(events::MouseScrollEvent& e);

		bool OnKeyPressedEvent(events::KeyPressedEvent& e);
		bool OnKeyReleasedEvent(events::KeyReleasedEvent& e);

		bool m_WindowResized_flag = false;
		bool m_Running = true;
	};
}