#include "pch.h"
#include "Mouse.h"

namespace renderx::base
{
	std::shared_ptr<Mouse> Mouse::s_Instance;

	std::shared_ptr<Mouse> Mouse::Get()
	{
		if (!s_Instance)
		{
			s_Instance = std::shared_ptr<Mouse>(new Mouse());
			return s_Instance;
		}
		return s_Instance;
	}

	void Mouse::OnEvent(MouseMovedEvent& event)
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

	void Mouse::OnEvent(MousePressedEvent& event)
	{

		if (event.GetMouseButton() == MouseButtonType::RX_LEFT_BUTTON)
		{
			m_LeftButton = true;
		}
		else if (event.GetMouseButton() == MouseButtonType::RX_RIGHT_BUTTON)
		{
			m_RightButton = true;
		}
		else if (event.GetMouseButton() == MouseButtonType::RX_MIDDLE_BUTTON)
		{

			m_MiddleButton = true;
		}

	}



	void Mouse::OnEvent(MouseRelasedEvent& event)
	{

		if (event.GetMouseButton() == MouseButtonType::RX_LEFT_BUTTON)
		{
			m_LeftButton = false;
		}
		else if (event.GetMouseButton() == MouseButtonType::RX_RIGHT_BUTTON)
		{
			m_RightButton = false;
		}
		else if (event.GetMouseButton() == MouseButtonType::RX_MIDDLE_BUTTON)
		{
			m_MiddleButton = false;
		}
	}

	void Mouse::OnEvent(MouseScrollEvent& event)
	{
		float xoffset = event.GetXOffset() * m_ScrollSensitivity;
		float yoffset = event.GetYOffset() * m_ScrollSensitivity;

		m_MouseScrollOffset = glm::vec2(xoffset, yoffset);
	}

	void Mouse::UpdateMouse()
	{
		m_LastPosition = m_CurrentPosition;
		m_MouseScrollOffset = glm::vec2(0.0f);
	}

	Mouse::Mouse()
		:m_CurrentPosition(glm::vec2(0.0f)),
		m_LastPosition(glm::vec2(0.0f)),
		m_MouseSensitivity(0.1f),
		m_ScrollSensitivity(0.08f),
		m_MouseScrollOffset(glm::vec2(0.0f))
	{
	
	}





}