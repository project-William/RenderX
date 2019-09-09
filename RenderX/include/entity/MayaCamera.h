#pragma once

#include "Entity.h"
#include "..//utils/Keyboard.h"
#include "..//utils/Mouse.h"
#include "..//graphics/imgui/ImguiSceneWindow.h"

namespace renderx {
	namespace entity {

		class REN_API MayaCamera :public Entity
		{
		public:
			MayaCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
				float yaw = -90, float pitch = 15.0f):m_FocusPoint(glm::vec3(0.0f))
			{
				m_CameraAttrib.Front = glm::vec3(0.0f, 0.0f, 0.0f);
				m_CameraAttrib.MouseSensivitity = 0.1f;
				m_CameraAttrib.MovementSpeed = 0.1f;
				m_CameraAttrib.Zoom = 45.0f;
				m_CameraAttrib.Position = glm::vec3(position.x, -position.y, position.z);
				m_CameraAttrib.WorldUp = up;
				m_CameraAttrib.Euler_Yaw = yaw;
				m_CameraAttrib.Euler_Pitch = pitch;
				
				OnUpdate();
			}

			~MayaCamera();

			void OnUpdate() override;
			void EnableObject() override;
			void DisableObject() override;

			glm::mat4 GetViewMatrix() ;
			inline CameraAttributes GetCameraAttrib() { return m_CameraAttrib; }
			inline float& GetDistanceRef() { return m_Distance; }
			inline bool& IsUseRef() { return m_IsUse; }
		private:
			CameraAttributes m_CameraAttrib;
			bool m_IsUse = false;
			float m_Distance;
			glm::vec3 m_FocusPoint;
			glm::mat4 m_RotationMatrix;
			glm::vec3 m_Position;

			void ProcessInputMouse();
			void ProcessMouseScrollInput();
			void UpdateCameraPosition();
			bool IsMouseInRange(const glm::vec2& position);
		};

	}
}