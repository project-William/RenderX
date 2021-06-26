#include "pch.h"
#include "BasicConfig.h"
#define BIND_EVENT(x) std::bind(&x, this, std::placeholders::_1)

namespace renderx::base
{
	BasicConfig::BasicConfig()
	{
		s_KeyboardInstance = Keyboard::Get();
		s_MouseInstance = Mouse::Get();
		s_MainWindowInstance = Window::Get();
		s_MainWindowInstance->SetEventCallback(BIND_EVENT(BasicConfig::OnEvent));

		m_Camera = Camera::Get();
		s_RenderScene = Core::RenderScene::Get();
	}

	void BasicConfig::OnEvent(Event& e)
	{
		bool handled = false;
		EventDispatcher dispatcher(e);

		if (e.IsInCategory(RX_EVENT_CATEGORY_WINDOW))
		{
			if (!handled)
			{
				handled = dispatcher.Dispatch<WindowResizedEvent>(BIND_EVENT(BasicConfig::OnWindowResizedEvent));
			}

			if (!handled)
			{
				handled = dispatcher.Dispatch<WindowClosedEvent>(BIND_EVENT(BasicConfig::OnWindowClosedEvent));
			}

			if (!handled)
			{
				handled = dispatcher.Dispatch<WindowMovedEvent>(BIND_EVENT(BasicConfig::OnWindowMovedEvent));
			}
		}

		else if (e.IsInCategory(RX_EVENT_CATEGORY_KEYBOARD))
		{
			if (!handled)
			{
				handled = dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT(BasicConfig::OnKeyPressedEvent));
			}

			if (!handled)
			{
				handled = dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT(BasicConfig::OnKeyReleasedEvent));
			}

		}

		else if (e.IsInCategory(RX_EVENT_CATEGORY_MOUSE))
		{
			if (!handled)
			{
				handled = dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT(BasicConfig::OnMouseMovedEvent));
			}

			if (!handled)
			{
				handled = dispatcher.Dispatch<MousePressedEvent>(BIND_EVENT(BasicConfig::OnMouseButtonPressed));
			}

			if (!handled)
			{
				handled = dispatcher.Dispatch<MouseRelasedEvent>(BIND_EVENT(BasicConfig::OnMouseButtonReleased));
			}

			if (!handled)
			{
				handled = dispatcher.Dispatch<MouseScrollEvent>(BIND_EVENT(BasicConfig::OnMouseScrollEvent));
			}
		}
	}

	bool BasicConfig::OnWindowResizedEvent(WindowResizedEvent& e)
	{
		//s_MainWindowInstance->OnWindowResized();
		m_WindowResized_flag = true;
		return true;
	}

	bool BasicConfig::OnWindowClosedEvent(WindowClosedEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool BasicConfig::OnWindowMovedEvent(WindowMovedEvent& e)
	{
		return true;
	}

	bool BasicConfig::OnMouseButtonPressed(MousePressedEvent& e)
	{
		Mouse::Get()->OnEvent(e);
		return true;
	}

	bool BasicConfig::OnMouseButtonReleased(MouseRelasedEvent& e)
	{
		Mouse::Get()->OnEvent(e);
		return true;
	}

	bool BasicConfig::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		Mouse::Get()->OnEvent(e);
		return true;
	}

	bool BasicConfig::OnMouseScrollEvent(MouseScrollEvent& e)
	{
		Mouse::Get()->OnEvent(e);
		return true;
	}

	bool BasicConfig::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		Keyboard::Get()->OnEvent(e);
		return true;
	}

	bool BasicConfig::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		Keyboard::Get()->OnEvent(e);
		return true;
	}


}