#pragma once
#include "Entity.h"
#include "..//utils/Keyboard.h"
#include "..//utils/Mouse.h"
#include "..//graphics/imgui/ImguiSceneWindow.h"

namespace renderx {
	namespace entity {

		class REN_API FPSCamera :public Entity
		{
		private:
			CameraAttributes m_CameraAttrib;
			float m_DeltaTime = 0.1f;
			bool m_First_Mouse = true;
					
		public:
			FPSCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), 
				glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), 
				float yaw = -90, float pitch = -0.0f)
			{
				m_CameraAttrib.Front = glm::vec3(0.0f, 0.0f, -1.0f);
				m_CameraAttrib.MouseSensivitity = 0.1f;
				m_CameraAttrib.MovementSpeed = 0.1f;
				m_CameraAttrib.Zoom = 45.0f;
				m_CameraAttrib.Position = glm::vec3(position.x, -position.y, position.z);
				m_CameraAttrib.WorldUp = up;
				m_CameraAttrib.Euler_Yaw = yaw;
				m_CameraAttrib.Euler_Pitch = pitch;
				OnUpdate();
			}

			~FPSCamera();

			inline CameraAttributes GetCameraAttrib()const { return m_CameraAttrib; }


			void EnableObject()  override;
			void DisableObject() override;
			glm::mat4 GetViewMatrix();

		private:
			void OnUpdate() override;
			void ProcessMouseScrollInput();
			void ProcessKeyboardInput();
			void ProcessMouseInput();
		};

	}
}