#include "entity/MayaCamera.h"

namespace renderx {
	namespace entity {
		
		
		MayaCamera::~MayaCamera()
		{

		}

		void MayaCamera::OnUpdate()
		{
			glm::vec3 front = m_FocusPoint - m_CameraAttrib.Position;
			front = glm::normalize(front);

			m_CameraAttrib.Right = glm::normalize(glm::cross(front, m_CameraAttrib.WorldUp));
			m_CameraAttrib.Up = glm::normalize(glm::cross(front, m_CameraAttrib.Right));
			
			m_Distance = std::sqrt(std::powf(m_CameraAttrib.Position.x, 2)
				+ std::powf(m_CameraAttrib.Position.y, 2)
				+ std::powf(m_CameraAttrib.Position.z, 2));
			

		}

		void MayaCamera::EnableObject()  
		{
			ProcessInputMouse();
		}

		void MayaCamera::DisableObject() 
		{

		}

		

		glm::mat4 MayaCamera::GetViewMatrix()
		{
			return glm::lookAt(m_CameraAttrib.Position,
				m_FocusPoint,
				m_CameraAttrib.Up);
		}

		glm::mat4 MayaCamera::GetProjectionMatrix()
		{
			return glm::mat4();
		}

		glm::mat4 MayaCamera::GetModelMatrix()
		{
			return glm::mat4();
		}

		void MayaCamera::ProcessInputMouse()
		{
			std::shared_ptr<utils::Mouse>& mouse = utils::Mouse::GetMouseInstance();

			glm::vec2 LastPosition = mouse->GetMouseLastPosition();
			glm::vec2 CurrentPosition = mouse->GetMouseCurrentPosition();

			float xoffset = CurrentPosition.x - LastPosition.x;
			float yoffset = -CurrentPosition.y + LastPosition.y;

			xoffset *= 0.1f;
			yoffset *= 0.1f;

			mouse->UpdateMouse();

			if (mouse->IsRightMousebuttonPressed())
			{
				m_CameraAttrib.Position += m_CameraAttrib.Right * 0.1f * xoffset;
				m_CameraAttrib.Position -= m_CameraAttrib.Up * 0.1f * yoffset;

				m_FocusPoint.x += 0.1f * xoffset;
				m_FocusPoint.y += 0.1f * yoffset;

				m_Distance = std::sqrt(std::powf(m_CameraAttrib.Position.x, 2)
					+ std::powf(m_CameraAttrib.Position.y, 2)
					+ std::powf(m_CameraAttrib.Position.z, 2));
			}

			if (mouse->IsLeftMousebuttonPressed())
			{

				m_CameraAttrib.Euler_Yaw -= xoffset;
				m_CameraAttrib.Euler_Pitch -= yoffset;

				m_CameraAttrib.Position.x = -m_Distance * cos(glm::radians(m_CameraAttrib.Euler_Yaw)) * cos(glm::radians(m_CameraAttrib.Euler_Pitch));

				m_CameraAttrib.Position.y = -m_Distance * sin(glm::radians(m_CameraAttrib.Euler_Pitch));

				m_CameraAttrib.Position.z = -m_Distance * cos(glm::radians(m_CameraAttrib.Euler_Pitch)) * sin(glm::radians(m_CameraAttrib.Euler_Yaw));

			}


			if (mouse->IsMiddleMousebuttonMoved())
			{
				std::shared_ptr<utils::Mouse>& mouse = utils::Mouse::GetMouseInstance();

				if (m_CameraAttrib.Zoom >= 1.0f && m_CameraAttrib.Zoom <= 45.0f)
					m_CameraAttrib.Zoom -= mouse->GetMouseScrollOffset().y;
				if (m_CameraAttrib.Zoom <= 1.0f)
					m_CameraAttrib.Zoom = 1.0f;
				if (m_CameraAttrib.Zoom >= 45.0f)
					m_CameraAttrib.Zoom = 45.0f;

			}

			OnUpdate();

		}

		void MayaCamera::ProcessInputKeyboard()
		{

		}

	}
}