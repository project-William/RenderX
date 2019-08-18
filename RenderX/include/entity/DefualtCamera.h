#pragma once

#include "Entity.h"
#include "..//utils/Keyboard.h"
#include "..//utils/Mouse.h"

namespace renderx {
	namespace entity {

		class REN_API DefaultCamera :public Entity
		{
		public:
			DefaultCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
				float yaw = -90, float pitch = 0)
			{

				m_CameraAttrib.Front = glm::vec3(0.0f, 0.0f, -1.0f);
				m_CameraAttrib.MouseSensivitity = 0.1f;
				m_CameraAttrib.MovementSpeed = 0.1f;
				m_CameraAttrib.Zoom = 45.0f;
				m_CameraAttrib.Position = position;
				m_CameraAttrib.WorldUp = up;
				m_CameraAttrib.Euler_Yaw = yaw;
				m_CameraAttrib.Euler_Pitch = pitch;


				OnUpdate();
			}

			~DefaultCamera();

			void OnUpdate() override;
			void EnableObject() override;
			void DisableObject() override;

			glm::mat4 GetViewMatrix() ;
			glm::mat4 GetProjectionMatrix();
			glm::mat4 GetModelMatrix();

			inline CameraAttributes GetCameraAttrib()const { return m_CameraAttrib; }

		private:
			CameraAttributes m_CameraAttrib;

			//objects that beyond z-Near will not be rendered
			float m_Near;

			//objects that behind z-Far will not be rendered
			float m_Far;
			float m_Distance;

			void ProcessInputMouse();
			void ProcessInputKeyboard();
		};

	}
}