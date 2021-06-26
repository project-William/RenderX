#pragma once
#include "Event/MouseEvent.h"

namespace renderx::base
{

	enum MouseButtonType
	{
		RX_LEFT_BUTTON,
		RX_RIGHT_BUTTON,
		RX_MIDDLE_BUTTON,
	};


	class Mouse
	{
	public:
		static std::shared_ptr<Mouse> Get();

		float& GetMouseSensitivityRef() { return m_MouseSensitivity; }
		float& GetScrollSensitivityRef() { return m_ScrollSensitivity; }

		float GetMouseSensitivityVal() const { return m_MouseSensitivity; }
		float GetScrollSensitivityVal() const { return m_ScrollSensitivity; }

		glm::vec2& GetMouseCurrentPositionRef() { return m_CurrentPosition; }
		glm::vec2& GetMouseLastPositionRef() { return m_LastPosition; }
		
		glm::vec2 GetMouseCurrentPositionVal() const { return m_CurrentPosition; }
		glm::vec2 GetMouseLastPositionVal() const { return m_LastPosition; }

		glm::vec2& GetMouseScrollOffsetRef() { return m_MouseScrollOffset; }
		glm::vec2 GetMouseScrollOffsetVal() const { return m_MouseScrollOffset; }

		bool IsMouseRightButtonPressed() { return m_RightButton; }

		void OnEvent(MouseMovedEvent& event);

		void OnEvent(MousePressedEvent& event);

		void OnEvent(MouseRelasedEvent& event);

		void OnEvent(MouseScrollEvent& event);

		void UpdateMouse();

	private:
		Mouse();
		static std::shared_ptr<Mouse> s_Instance;

		bool m_LeftButton = false;
		bool m_RightButton = false;
		bool m_MiddleButton = true;

		glm::vec2 m_CurrentPosition;
		glm::vec2 m_LastPosition;

		float m_ScrollSensitivity;
		float m_MouseSensitivity;


		glm::vec2 m_MouseScrollOffset;
	};
}