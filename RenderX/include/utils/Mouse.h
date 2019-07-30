#pragma once
#include "..//..//Core.h"
#include "..//events/MouseEvent.h"
#include "..//graphics/Window.h"

namespace renderx {
	namespace utils {

		enum REN_API MouseButton
		{
			RX_LEFT_BUTTON,
			RX_RIGHT_BUTTON,
			RX_MIDDLE_BUTTON
		};

		class REN_API Mouse
		{
		private:
			bool m_LeftButton = false;
			bool m_RightButton = false;
			bool m_MiddleButton = false;

			glm::vec2 m_CurrentPosition;
			glm::vec2 m_LastPosition = glm::vec2(0.0f);
			glm::vec2 m_ScrollOffset = glm::vec2(0.0f);

			float m_ScrollSensitivity = 0.25f;
			float m_MouseSensitivity = 0.1;


			static std::shared_ptr<Mouse> ms_Mouse;
			Mouse();
		public:
			~Mouse();
			static std::shared_ptr<Mouse> Create();

			static std::shared_ptr<Mouse>& GetMouseInstance() { return ms_Mouse; }

			inline glm::vec2& GetMouseLastPosition() { return m_LastPosition; }

			inline glm::vec2& GetMouseCurrentPosition() { return m_CurrentPosition; }

			inline glm::vec2 GetMouseScrollOffset()const { return m_ScrollOffset; }

			inline float GetMouseSensitivity()const { return m_MouseSensitivity; }

			inline float GetScrollSensitivity()const { return m_ScrollSensitivity; }

			void OnEvent(events::MouseMovedEvent& event);
			
			void OnEvent(events::MousePressedEvent& event);
			
			void OnEvent(events::MouseRelasedEvent& event);
			
			void OnEvent(events::MouseScrollEvent& event);

			void UpdateMouse();

		};

	}
}