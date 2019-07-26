#pragma once
#include "utils/Mouse.h"

namespace renderx {
	namespace utils {

		std::shared_ptr<Mouse> Mouse::ms_Mouse = nullptr;

		Mouse::Mouse()
			:m_ScrollSensitivity(0.1), m_ScrollOffset(glm::vec2(0.0f)),
			 m_LastPosition(glm::vec2(0.0f)), m_Position(glm::vec2(0.0f)),
			 m_LeftButton(false), m_RightButton(false), 
			 m_MiddleButton(false),m_MouseSensitivity(0.1)
		{

		}

		Mouse::~Mouse()
		{

		}
		
		std::shared_ptr<Mouse> Mouse::Create()
		{
			if (!ms_Mouse)
			{
				ms_Mouse = std::shared_ptr<Mouse>(new Mouse());
				return ms_Mouse;
			}
			return ms_Mouse;
		}

		void Mouse::OnEvent(events::MouseMovedEvent& event)
		{
			m_LastPosition = m_Position;
			
			float xoffset = event.GetMouseXPos() - m_Position.x;
			float yoffset = event.GetMouseYPos() - m_Position.y;

			xoffset *= m_MouseSensitivity;
			yoffset *= m_MouseSensitivity;

			m_Position.x += xoffset;
			m_Position.y += yoffset;

		}

		void Mouse::OnEvent(events::MousePressedEvent& event)
		{
			if (event.GetMouseButton() == RX_MOUSE_LEFT)
			{
				m_LeftButton = true;
			}
			else if (event.GetMouseButton() == RX_MOUSE_MIDDLE)
			{
				m_MiddleButton = true;
			}
			else if (event.GetMouseButton() == RX_MOUSE_RIGHT)
			{
				m_RightButton = true;
			}
		}

		void Mouse::OnEvent(events::MouseRelasedEvent& event)
		{
			if (event.GetMouseButton() == RX_MOUSE_LEFT)
			{
				m_LeftButton = false;
			}
			else if (event.GetMouseButton() == RX_MOUSE_MIDDLE)
			{
				m_MiddleButton = false;
			}
			else if (event.GetMouseButton() == RX_MOUSE_RIGHT)
			{
				m_RightButton = false;
			}
		}

		void Mouse::OnEvent(events::MouseScrollEvent& event)
		{
			float xoffset = event.GetXOffset() * m_ScrollSensitivity;
			float yoffset = event.GetYOffset() * m_ScrollSensitivity;
			
			m_ScrollOffset = glm::vec2(xoffset, yoffset);
		}

		void Mouse::Update()
		{
			m_LastPosition = m_Position;
			m_ScrollOffset = glm::vec2(0.0f);
		}

	}
}