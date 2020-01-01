#include "Configuration.h"

namespace renderx
{
	Configuration::Configuration()
	{
		m_Window = Window::Create();
		m_Keyboard = utils::Keyboard::Create();
		m_Mouse = utils::Mouse::Create();
		m_Window->SetEventCallback(BIND_EVENT(Configuration::OnEvent));
	}

	Configuration::~Configuration()
	{
	}

	void Configuration::OnEvent(events::Event& e)
	{
		bool handled = false;
		events::EventDispatcher dispatcher(e);

		if (e.IsInCategory(events::RX_EVENT_CATEGORY_WINDOW))
		{
			if (!handled)
			{
				handled = dispatcher.Dispatch<events::WindowResizedEvent>(BIND_EVENT(Configuration::OnWindowResizedEvent));
			}

			if (!handled)
			{
				handled = dispatcher.Dispatch<events::WindowClosedEvent>(BIND_EVENT(Configuration::OnWindowClosedEvent));
			}

			if (!handled)
			{
				handled = dispatcher.Dispatch<events::WindowMovedEvent>(BIND_EVENT(Configuration::OnWindowMovedEvent));
			}
		}

		else if (e.IsInCategory(events::RX_EVENT_CATEGORY_KEYBOARD))
		{
			if (!handled)
			{
				handled = dispatcher.Dispatch<events::KeyPressedEvent>(BIND_EVENT(Configuration::OnKeyPressedEvent));
			}

			if (!handled)
			{
				handled = dispatcher.Dispatch<events::KeyReleasedEvent>(BIND_EVENT(Configuration::OnKeyReleasedEvent));
			}

		}

		else if (e.IsInCategory(events::RX_EVENT_CATEGORY_MOUSE))
		{
			if (!handled)
			{
				handled = dispatcher.Dispatch<events::MouseMovedEvent>(BIND_EVENT(Configuration::OnMouseMovedEvent));
			}

			if (!handled)
			{
				handled = dispatcher.Dispatch<events::MousePressedEvent>(BIND_EVENT(Configuration::OnMouseButtonPressed));
			}

			if (!handled)
			{
				handled = dispatcher.Dispatch<events::MouseRelasedEvent>(BIND_EVENT(Configuration::OnMouseButtonReleased));
			}

			if (!handled)
			{
				handled = dispatcher.Dispatch<events::MouseScrollEvent>(BIND_EVENT(Configuration::OnMouseScrollEvent));
			}
		}
	}

	bool Configuration::OnWindowResizedEvent(events::WindowResizedEvent& e)
	{
		m_Window->OnWindowResized();
		m_WindowResized_flag = true;
		return true;
	}

	bool Configuration::OnWindowClosedEvent(events::WindowClosedEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Configuration::OnWindowMovedEvent(events::WindowMovedEvent& e)
	{
		return true;
	}

	bool Configuration::OnMouseButtonPressed(events::MousePressedEvent& e)
	{
		utils::Mouse::GetMouseInstance()->OnEvent(e);
		return true;
	}

	bool Configuration::OnMouseButtonReleased(events::MouseRelasedEvent& e)
	{
		utils::Mouse::GetMouseInstance()->OnEvent(e);
		return true;
	}

	bool Configuration::OnMouseMovedEvent(events::MouseMovedEvent& e)
	{
		utils::Mouse::GetMouseInstance()->OnEvent(e);
		return true;
	}

	bool Configuration::OnMouseScrollEvent(events::MouseScrollEvent& e)
	{
		utils::Mouse::GetMouseInstance()->OnEvent(e);
		return true;
	}

	bool Configuration::OnKeyPressedEvent(events::KeyPressedEvent& e)
	{
		utils::Keyboard::GetKeyboardInstance()->OnEvent(e);
		return true;
	}

	bool Configuration::OnKeyReleasedEvent(events::KeyReleasedEvent& e)
	{
		utils::Keyboard::GetKeyboardInstance()->OnEvent(e);
		return true;
	}



}