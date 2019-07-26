#pragma once
#include "..//Core.h"
#include "..//events/MouseEvent.h"

namespace renderx {
	namespace utils {

		enum REN_API MouseButton
		{
			RX_MOUSE_LEFT = 0,
			RX_MOUSE_RIGHT,
			RX_MOUSE_MIDDLE
		};


		class REN_API Mouse
		{
		private:
			bool m_LeftButton;
			bool m_RightButton;
			bool m_MiddleButton;

			float m_ScrollSensitivity;
			float m_MouseSensitivity;

			glm::vec2 m_Position;
			glm::vec2 m_LastPosition;
			glm::vec2 m_ScrollOffset;

			static std::shared_ptr<Mouse> ms_Mouse;
			Mouse();
			~Mouse();
			
		public:

			static std::shared_ptr<Mouse> Create();

			static const std::shared_ptr<Mouse>& GetMouseInstance() { return ms_Mouse; }
			
			inline bool IsLeftButtonPressed()const { return m_LeftButton; }
			
			inline bool IsRightButtonPressed()const { return m_RightButton; }
			
			inline bool IsMiddleButtonPressed()const { return m_MiddleButton; }

			void OnEvent(events::MouseMovedEvent& event);

			void OnEvent(events::MousePressedEvent& event);
			
			void OnEvent(events::MouseRelasedEvent& event);
			
			void OnEvent(events::MouseScrollEvent& event);

			void Update();
			
			inline const glm::vec2& GetPosition()const { return m_Position; }

			inline const glm::vec2& GetLastPosition()const { return m_LastPosition; }
			
			inline const glm::vec2& GetScrollOffset()const { return m_ScrollOffset; }

		};

	}
}