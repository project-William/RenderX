#include "entity/FPSCamera.h"

namespace renderx {
	namespace entity {

		FPSCamera::~FPSCamera()
		{

		}

		void FPSCamera::OnUpdate()
		{
			glm::vec3 front;
			front.x = cos(glm::radians(m_CameraAttrib.Euler_Yaw)) * cos(glm::radians(m_CameraAttrib.Euler_Pitch));
			front.y = sin(glm::radians(m_CameraAttrib.Euler_Pitch));
			front.z = sin(glm::radians(m_CameraAttrib.Euler_Yaw)) * cos(glm::radians(m_CameraAttrib.Euler_Pitch));
			m_CameraAttrib.Front = glm::normalize(front);

			m_CameraAttrib.Right = glm::normalize(glm::cross(m_CameraAttrib.Front, m_CameraAttrib.WorldUp));
			m_CameraAttrib.Up = glm::normalize(glm::cross(m_CameraAttrib.Front, m_CameraAttrib.Right));
		}

		void FPSCamera::EnableObject()  
		{
			ProcessMouseScrollInput();
			ProcessMouseInput();
			ProcessKeyboardInput();
		}

		void FPSCamera::DisableObject() 
		{

		}

		glm::mat4 FPSCamera::GetViewMatrix()
		{
			return glm::lookAt(m_CameraAttrib.Position, 
						       m_CameraAttrib.Position + m_CameraAttrib.Front, 
							   m_CameraAttrib.Up);
		}

		void FPSCamera::ProcessMouseInput()
		{	
			float speed = 0.005f;
			std::shared_ptr<utils::Mouse>& mouse = utils::Mouse::GetMouseInstance();
		
			if (mouse->GetMouseCurrentPosition() != glm::vec2(0, 0))
			{
				glm::vec2 LastPosition = mouse->GetMouseLastPosition();
				glm::vec2 CurrentPosition = mouse->GetMouseCurrentPosition();
				if (m_First_Mouse)
				{
					LastPosition = CurrentPosition;
					m_First_Mouse = false;
				}

				float xoffset = CurrentPosition.x - LastPosition.x;
				float yoffset = -CurrentPosition.y + LastPosition.y;

				mouse->UpdateMouse();

				xoffset *= mouse->GetMouseSensitivity();
				yoffset *= mouse->GetMouseSensitivity();

				m_CameraAttrib.Euler_Yaw -= xoffset;
				m_CameraAttrib.Euler_Pitch -= yoffset;

				if (m_CameraAttrib.Euler_Pitch >= 89.0f)
					m_CameraAttrib.Euler_Pitch = 89.0f;
				if (m_CameraAttrib.Euler_Pitch <= -89.0f)
					m_CameraAttrib.Euler_Pitch = -89.0f;

				OnUpdate();

			}
		}

		void FPSCamera::ProcessMouseScrollInput()
		{
			std::shared_ptr<utils::Mouse>& mouse = utils::Mouse::GetMouseInstance();

			if (m_CameraAttrib.Zoom>= 1.0f && m_CameraAttrib.Zoom <= 45.0f)
				m_CameraAttrib.Zoom -= mouse->GetMouseScrollOffset().y;
			if (m_CameraAttrib.Zoom <= 1.0f)
				m_CameraAttrib.Zoom = 1.0f;
			if (m_CameraAttrib.Zoom >= 45.0f)
				m_CameraAttrib.Zoom = 45.0f;

			std::cout << mouse->GetMouseScrollOffset().y << std::endl;

		}

		void FPSCamera::ProcessKeyboardInput()
		{
			float speed = 0.05f;
			std::shared_ptr<utils::Keyboard>& keyboard = utils::Keyboard::GetKeyboardInstance();

			if (keyboard->GetKeyCode(utils::Keys::RX_KEY_W))
			{
				m_CameraAttrib.Position += speed * m_CameraAttrib.Front;
				std::cout << "Key w pressed" << std::endl;
			}
			else if (keyboard->GetKeyCode(utils::Keys::RX_KEY_A))
			{
				m_CameraAttrib.Position += speed * m_CameraAttrib.Right;
				std::cout << "Key A pressed" << std::endl;
			}
			else if (keyboard->GetKeyCode(utils::Keys::RX_KEY_S))
			{
				m_CameraAttrib.Position -= speed * m_CameraAttrib.Front;
				std::cout << "Key s pressed" << std::endl;
			}
			else if (keyboard->GetKeyCode(utils::Keys::RX_KEY_D))
			{
				m_CameraAttrib.Position -= speed * m_CameraAttrib.Right;
				std::cout << "Key D pressed" << std::endl;
			}

			OnUpdate();
		}


	}
}