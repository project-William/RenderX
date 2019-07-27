#include "entity/FPSCamera.h"

namespace renderx {
	namespace entity {

		FPSCamera::FPSCamera(glm::vec3 position = glm::vec3(0.0f),
						     glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
						     float yaw = YAW, float pitch = PITCH)
		{
			m_CameraAttrib.Euler_Pitch = pitch;
			m_CameraAttrib.Euler_Yaw = yaw;
			m_CameraAttrib.Front = glm::vec3(0.0f, 0.0f, -1.0f);
			m_CameraAttrib.MouseSensivitity = SENSITIVITY;
			m_CameraAttrib.Position = position;
			m_CameraAttrib.WorldUp = up;
			UpdateCameraMatrix();
		}

		FPSCamera::~FPSCamera()
		{

		}

		void FPSCamera::OnUpdate()
		{

		}

		void FPSCamera::EnableObject()
		{

		}

		void FPSCamera::DisableObject()
		{

		}

		glm::mat4 FPSCamera::GetViewMatrix()
		{
			
		}

		void FPSCamera::UpdateCameraMatrix()
		{

		}


	}
}