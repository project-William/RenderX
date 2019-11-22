#include "Window.h"
#include "utils/Mouse.h"

namespace renderx 
{
	namespace utils 
	{

		std::shared_ptr<Mouse> Mouse::ms_Mouse;

		Mouse::Mouse()
		{ }

		Mouse::~Mouse()
		{ }

		std::shared_ptr<Mouse> Mouse::Create()
		{
			if (ms_Mouse == nullptr)
			{
				ms_Mouse = std::shared_ptr<Mouse>(new Mouse());
				return ms_Mouse;
			}
			return ms_Mouse;
		}

		void Mouse::OnEvent(events::MouseMovedEvent& event)
		{
			m_LastPosition = m_CurrentPosition;

			float xoffset = event.GetMouseXPos() - m_LastPosition.x;
			float yoffset = event.GetMouseYPos() - m_LastPosition.y;

			xoffset *= m_MouseSensitivity;
			yoffset *= m_MouseSensitivity;

			m_CurrentPosition.x += xoffset;
			m_CurrentPosition.y += yoffset;

			m_CurrentPosition = event.GetMousePos();
		}

		void Mouse::OnEvent(events::MousePressedEvent& event)
		{
			if (event.GetMouseButton() == MouseButton::RX_LEFT_BUTTON)
			{
				m_LeftButton = true;
			}
			else if (event.GetMouseButton() == MouseButton::RX_RIGHT_BUTTON)
			{
				m_RightButton = true;
			}
			else if (event.GetMouseButton() == MouseButton::RX_MIDDLE_BUTTON)
			{
				m_MiddleButton = true;
			}
		}



		void Mouse::OnEvent(events::MouseRelasedEvent& event)
		{

			if (event.GetMouseButton() == MouseButton::RX_LEFT_BUTTON)
			{
				m_LeftButton = false;
			}
			else if (event.GetMouseButton() == MouseButton::RX_RIGHT_BUTTON)
			{
				m_RightButton = false;
			}
			else if (event.GetMouseButton() == MouseButton::RX_MIDDLE_BUTTON)
			{
				m_MiddleButton = false;
			}
		}

		void Mouse::OnEvent(events::MouseScrollEvent& event)
		{
			float xoffset = event.GetXOffset() * m_ScrollSensitivity;
			float yoffset = event.GetYOffset() * m_ScrollSensitivity;

			m_ScrollOffset = glm::vec2(xoffset, yoffset);
		}

		void Mouse::UpdateMouse()
		{
			m_LastPosition = m_CurrentPosition;
			m_ScrollOffset = glm::vec2(0.0f);
		}

	}
}