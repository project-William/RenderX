#include "entity/Camera.h"
#include "utils/Keyboard.h"
#include "utils/Mouse.h"
#include "Window.h"

namespace renderx::entity
{
	Camera::Camera(const glm::vec3& position)
	{
		m_CamAttrib.Zoom = 45.0f;
		m_CamAttrib.Front = glm::vec3(0.0f, 0.0f, 3.0f);
		m_CamAttrib.Up = glm::vec3(0.0f, -1.0f, 0.0f);
		m_CamAttrib.WorldUp = m_CamAttrib.Up;
		m_CamAttrib.Yaw = -90.0f;
		m_CamAttrib.Pitch = 0.0f;
		m_CamAttrib.Position = position;
		m_CamAttrib.FocusPoint = glm::vec3(0.0f);

		OnUpdate();
	}

	Camera::~Camera()
	{
	}

	void Camera::OnUpdate()
	{
		glm::vec3 front = m_CamAttrib.FocusPoint - m_CamAttrib.Position;
		front = glm::normalize(front);

		m_CamAttrib.Right = glm::normalize(glm::cross(front, m_CamAttrib.WorldUp));
		m_CamAttrib.Up = glm::normalize(glm::cross(front, m_CamAttrib.Right));
	}

	void Camera::ProcessMouseInput()
	{
		std::shared_ptr<utils::Mouse> mouse = utils::Mouse::GetMouseInstance();

		glm::vec2 LastPosition = mouse->GetMouseLastPosition();
		glm::vec2 CurrentPosition = mouse->GetMouseCurrentPosition();

		float xoffset = CurrentPosition.x - LastPosition.x;
		float yoffset = -CurrentPosition.y + LastPosition.y;

		xoffset *= 0.1f;
		yoffset *= 0.1f;

		if (mouse->IsRightMousebuttonPressed())
		{
			m_CamAttrib.Yaw -= xoffset;
			m_CamAttrib.Pitch -= yoffset;
			UpdateCameraPosition();
		}
		mouse->UpdateMouse();

		m_Distance = std::sqrt(std::powf(m_CamAttrib.Position.x, 2)
			+ std::powf(m_CamAttrib.Position.y, 2)
			+ std::powf(m_CamAttrib.Position.z, 2));

		OnUpdate();

	}

	void Camera::ProcessMouseScrollInput()
	{
		std::shared_ptr<utils::Mouse> mouse = utils::Mouse::GetMouseInstance();

		m_Distance = std::sqrt(std::powf(m_CamAttrib.Position.x, 2)
			+ std::powf(m_CamAttrib.Position.y, 2)
			+ std::powf(m_CamAttrib.Position.z, 2));

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

		OnUpdate();
	}

	void Camera::ProcessKeyboardInput()
	{
		auto keyboard = utils::Keyboard::GetKeyboardInstance();

		float angle = 5.0f;

		if (keyboard->GetKeyCode(utils::Keys::RX_KEY_W))
		{

			std::cout << "Key w pressed" << std::endl;
		}
		else if (keyboard->GetKeyCode(utils::Keys::RX_KEY_A))
		{

			std::cout << "Key A pressed" << std::endl;
		}
		else if (keyboard->GetKeyCode(utils::Keys::RX_KEY_S))
		{

			std::cout << "Key s pressed" << std::endl;
		}
		else if (keyboard->GetKeyCode(utils::Keys::RX_KEY_D))
		{

			std::cout << "Key D pressed" << std::endl;
		}

		UpdateCameraPosition();
		OnUpdate();
	}

	void Camera::UpdateCameraPosition()
	{
		m_CamAttrib.Position.x = -m_Distance * cos(glm::radians(m_CamAttrib.Yaw)) * cos(glm::radians(m_CamAttrib.Pitch));
		m_CamAttrib.Position.y = +m_Distance * sin(glm::radians(m_CamAttrib.Pitch));
		m_CamAttrib.Position.z = +m_Distance * cos(glm::radians(m_CamAttrib.Pitch)) * sin(glm::radians(m_CamAttrib.Yaw));
	}

	glm::mat4 Camera::GetViewMatrix()
	{
		return glm::lookAt(m_CamAttrib.Position,
			m_CamAttrib.FocusPoint,
			m_CamAttrib.Up);
	}

	glm::mat4 Camera::GetProjectionMatrix(float zoom)
	{
		float aspect = static_cast<float>(Window::GetWindowInstance()->GetWidth()) / Window::GetWindowInstance()->GetHeight();
		return glm::perspective(glm::radians(zoom), ASPECT_IN_RANGE(aspect), 0.1f, 100.0f);
	}

	void Camera::EnableObject()
	{
		ProcessMouseScrollInput();
		ProcessMouseInput();
		//ProcessKeyboardInput();
	}

}