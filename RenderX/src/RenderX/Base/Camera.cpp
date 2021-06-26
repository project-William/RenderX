#include "pch.h"
#include "Camera.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Window.h"

#define ASPECT_IN_RANGE(x) isnan(x) == true ? 1.0f : x

namespace renderx::base
{
	std::shared_ptr<Camera> Camera::s_Instance;

	std::shared_ptr<Camera>& Camera::Get()
	{
		if (!s_Instance)
		{
			s_Instance = std::shared_ptr<Camera>(new Camera());
		}
		return s_Instance;
	}

	Camera::Camera()
	{
		m_CamAttrib.Zoom = 45.0f;
		m_CamAttrib.Front = glm::vec3(0.0f, 0.0f, 3.0f);
		m_CamAttrib.Up = glm::vec3(0.0f, -1.0f, 0.0f);
		m_CamAttrib.WorldUp = m_CamAttrib.Up;
		m_CamAttrib.Yaw = -90.0f;
		m_CamAttrib.Pitch = 30.0f;
		m_CamAttrib.Position = glm::vec3(0.0f, 15.0f*sqrt(3)/3, -15.0f);
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
		std::shared_ptr<Mouse> mouse = Mouse::Get();

		glm::vec2 LastPosition = mouse->GetMouseLastPositionVal();
		glm::vec2 CurrentPosition = mouse->GetMouseCurrentPositionVal();

		float xoffset = CurrentPosition.x - LastPosition.x;
		float yoffset = -CurrentPosition.y + LastPosition.y;

		xoffset *= 0.1f;
		yoffset *= 0.1f;


		if (mouse->IsMouseRightButtonPressed())
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
		std::shared_ptr<Mouse> mouse = Mouse::Get();

		m_Distance = std::sqrt(std::powf(m_CamAttrib.Position.x, 2)
			+ std::powf(m_CamAttrib.Position.y, 2)
			+ std::powf(m_CamAttrib.Position.z, 2));

		if (mouse->GetMouseScrollOffsetVal().y < 0)
		{
			m_Distance -= mouse->GetMouseScrollOffsetVal().y;
			UpdateCameraPosition();
		}
		if (m_Distance <= 0.1f)
		{
			m_Distance = 0.1f;
			UpdateCameraPosition();
		}
		if (mouse->GetMouseScrollOffsetVal().y > 0)
		{
			m_Distance -= mouse->GetMouseScrollOffsetVal().y;
			UpdateCameraPosition();
		}

		OnUpdate();
	}

	void Camera::ProcessKeyboardInput()
	{
		auto keyboard = Keyboard::Get();

		float angle = 5.0f;

		if (keyboard->GetKeyCode(Keys::RX_KEY_W))
		{

			std::cout << "Key w pressed" << std::endl;
		}
		else if (keyboard->GetKeyCode(Keys::RX_KEY_A))
		{

			std::cout << "Key A pressed" << std::endl;
		}
		else if (keyboard->GetKeyCode(Keys::RX_KEY_S))
		{

			std::cout << "Key s pressed" << std::endl;
		}
		else if (keyboard->GetKeyCode(Keys::RX_KEY_D))
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
		m_ViewMatrix = glm::lookAt(m_CamAttrib.Position,
			m_CamAttrib.FocusPoint,
			m_CamAttrib.Up);
		return m_ViewMatrix;
	}

	//glm::mat4 Camera::GetProjectionMatrix(float zoom)
	//{
	//	auto data = Window::Get()->GetWinDataVal();
	//	float aspect = static_cast<float>(data.m_Width / data.m_Height);
	//	m_ProjectionMatrix = glm::perspective(glm::radians(45.0f), ASPECT_IN_RANGE(aspect), 0.01f, 100.0f);
	//	return m_ProjectionMatrix;
	//}

	glm::mat4 Camera::GetProjectionMatrix()
	{
		return m_ProjectionMatrix;
	}

	void Camera::SetProjectionMatrix(int x,int y)
	{
		float aspect = static_cast<float>(1.0f* x / y);
		m_ProjectionMatrix = glm::perspective(glm::radians(45.0f), ASPECT_IN_RANGE(aspect), 0.01f, 100.0f);
	}


	void Camera::EnableInputEvent()
	{
		ProcessMouseScrollInput();
		ProcessMouseInput();
		ProcessKeyboardInput();
	}
}