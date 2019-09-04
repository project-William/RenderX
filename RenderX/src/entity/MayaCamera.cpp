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
			
		}

		void MayaCamera::EnableObject()  
		{
			ProcessMouseScrollInput();
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

			auto sceneWindow = ui::ImguiSceneWindow::GetSceneWindowInstance();
			std::cout << sceneWindow->GetSceneWinHeight() << std::endl;

			if (mouse->GetMouseCurrentPosition().x <= sceneWindow->GetSceneWinWidth()
				&& mouse->GetMouseCurrentPosition().y <= sceneWindow->GetSceneWinHeight()
			   )
			{
				if (mouse->IsLeftMousebuttonPressed())
				{
					m_CameraAttrib.Euler_Yaw -= xoffset;
					m_CameraAttrib.Euler_Pitch -= yoffset;
					UpdateCameraPosition();
				}

			}
		
			mouse->UpdateMouse();

			m_Distance = std::sqrt(std::powf(m_CameraAttrib.Position.x, 2)
				+ std::powf(m_CameraAttrib.Position.y, 2)
				+ std::powf(m_CameraAttrib.Position.z, 2));

			OnUpdate();

		}

		void MayaCamera::UpdateCameraPosition()
		{
			m_CameraAttrib.Position.x = -m_Distance * cos(glm::radians(m_CameraAttrib.Euler_Yaw)) * cos(glm::radians(m_CameraAttrib.Euler_Pitch));

			m_CameraAttrib.Position.y = -m_Distance * sin(glm::radians(m_CameraAttrib.Euler_Pitch));

			m_CameraAttrib.Position.z = -m_Distance * cos(glm::radians(m_CameraAttrib.Euler_Pitch)) * sin(glm::radians(m_CameraAttrib.Euler_Yaw));

		}

		void MayaCamera::ProcessMouseScrollInput()
		{
			std::shared_ptr<utils::Mouse>& mouse = utils::Mouse::GetMouseInstance();
			auto sceneWindow = ui::ImguiSceneWindow::GetSceneWindowInstance();

			m_Distance = std::sqrt(std::powf(m_CameraAttrib.Position.x, 2)
				+ std::powf(m_CameraAttrib.Position.y, 2)
				+ std::powf(m_CameraAttrib.Position.z, 2));

			if (mouse->GetMouseCurrentPosition().x <= sceneWindow->GetSceneWinWidth()
				&& mouse->GetMouseCurrentPosition().y <= sceneWindow->GetSceneWinHeight()
				)
			{
				if (mouse->GetMouseScrollOffset().y < 0)
				{
					m_Distance -= mouse->GetMouseScrollOffset().y;
					UpdateCameraPosition();
				}
				if (m_Distance <= 1.0f)
				{
					m_Distance = 1.0f;
					UpdateCameraPosition();
				}
				if (mouse->GetMouseScrollOffset().y > 0)
				{
					m_Distance -= mouse->GetMouseScrollOffset().y;
					UpdateCameraPosition();
				}
			}

			OnUpdate();

		}


	}
}