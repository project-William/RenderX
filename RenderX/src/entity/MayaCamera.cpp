#include "entity/MayaCamera.h"

namespace renderx {
	namespace entity {
		
		
		MayaCamera::~MayaCamera()
		{

		}

		void MayaCamera::OnUpdate()
		{
			if (utils::Mouse::GetMouseInstance()->IsLeftMousebuttonPressed())
			{
				glm::vec3 front;
				front.x = cos(glm::radians(m_CameraAttrib.Euler_Yaw)) * cos(glm::radians(m_CameraAttrib.Euler_Pitch));
				front.y = sin(glm::radians(m_CameraAttrib.Euler_Pitch));
				front.z = sin(glm::radians(m_CameraAttrib.Euler_Yaw)) * cos(glm::radians(m_CameraAttrib.Euler_Pitch));
				m_CameraAttrib.Front = glm::normalize(front);

				m_CameraAttrib.Right = glm::normalize(glm::cross(m_CameraAttrib.Front, m_CameraAttrib.WorldUp));
				m_CameraAttrib.Up = glm::normalize(glm::cross(m_CameraAttrib.Front, m_CameraAttrib.Right));

			}
			else
			{
				glm::vec3 front;
				front.x = cos(glm::radians(m_CameraAttrib.Euler_Yaw)) * cos(glm::radians(m_CameraAttrib.Euler_Pitch));
				front.y = sin(glm::radians(m_CameraAttrib.Euler_Pitch));
				front.z = sin(glm::radians(m_CameraAttrib.Euler_Yaw)) * cos(glm::radians(m_CameraAttrib.Euler_Pitch));
				m_CameraAttrib.Front = glm::normalize(front);

				m_CameraAttrib.Right = glm::normalize(glm::cross(m_CameraAttrib.Front, m_CameraAttrib.WorldUp));
				m_CameraAttrib.Up = glm::normalize(glm::cross(m_CameraAttrib.Front, m_CameraAttrib.Right));

			}
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

			if (utils::Mouse::GetMouseInstance()->IsRightMousebuttonPressed())
			{
				return glm::lookAt(m_CameraAttrib.Position,
					   m_CameraAttrib.Position + m_CameraAttrib.Front,
					   m_CameraAttrib.Up);
			}
			else if(utils::Mouse::GetMouseInstance()->IsLeftMousebuttonPressed())
			{
				return glm::lookAt(m_CameraAttrib.Position,
					   glm::vec3(0.0f),
					   m_CameraAttrib.Up);
			}
			else
			{
				return glm::lookAt(m_CameraAttrib.Position,
					   m_CameraAttrib.Position + m_CameraAttrib.Front,
					   m_CameraAttrib.Up);

			}
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


			mouse->UpdateMouse();

			if (mouse->IsRightMousebuttonPressed())
			{
				m_CameraAttrib.Position.x += xoffset * 0.01;
				m_CameraAttrib.Position.y += yoffset * 0.01;

			}

			if (mouse->IsLeftMousebuttonPressed())
			{

				//m_CameraAttrib.Euler_Yaw -= xoffset;
				//m_CameraAttrib.Euler_Pitch -= yoffset;

			}

			if (mouse->IsMiddleMousebuttonMoved())
			{

			}

			OnUpdate();

			//if (mouse->IsLeftMousebuttonPressed())
			//{
			//
			//}
			//
			//if (mouse->IsMiddleMousebuttonMoved())
			//{
			//	if (m_CameraAttrib.Zoom >= 1.0f && m_CameraAttrib.Zoom <= 45.0f)
			//		m_CameraAttrib.Zoom -= mouse->GetMouseScrollOffset().y;
			//	if (m_CameraAttrib.Zoom <= 1.0f)
			//		m_CameraAttrib.Zoom = 1.0f;
			//	if (m_CameraAttrib.Zoom >= 45.0f)
			//		m_CameraAttrib.Zoom = 45.0f;
			//}


		}

		void MayaCamera::ProcessInputKeyboard()
		{
		}


	}
}