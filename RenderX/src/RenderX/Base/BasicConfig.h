#pragma once
#include "pch.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Window.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"
#include "Event/WindowEvent.h"
#include "Camera.h"
#include "../Core/RenderScene.h"

namespace renderx::base
{
	class BasicConfig
	{
	public:
		BasicConfig();
		~BasicConfig() {}

		void OnEvent(Event& e);

	protected:

		bool OnWindowResizedEvent(WindowResizedEvent& e);
		bool OnWindowClosedEvent(WindowClosedEvent& e);
		bool OnWindowMovedEvent(WindowMovedEvent& e);

		bool OnMouseButtonPressed(MousePressedEvent& e);
		bool OnMouseButtonReleased(MouseRelasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrollEvent(MouseScrollEvent& e);

		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);

		std::shared_ptr<Mouse> s_MouseInstance;
		std::shared_ptr<Keyboard> s_KeyboardInstance;
		std::shared_ptr<Window> s_MainWindowInstance;
		std::shared_ptr<Camera> m_Camera;
		std::shared_ptr<Core::RenderScene> s_RenderScene;

		bool m_WindowResized_flag = false;
		bool m_Running = true;
	};
}