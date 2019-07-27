#pragma once
#pragma once
#include "..//Core.h"

namespace renderx {
	namespace entity {

		// Default camera values
		const float YAW = -90.0f;
		const float PITCH = 0.0f;
		const float SPEED = 2.5f;
		const float SENSITIVITY = 0.1f;
		const float ZOOM = 45.0f;

		//camera movement
		enum REN_API CameraMovement
		{
			CAMERA_MOVEMENT_LEFT,
			CAMERA_MOVEMENT_RIGHT,
			CAMERA_MOVEMENT_FORWARD,
			CAMERA_MOVEMENT_BACKWARD
		};

		//camera attributes
		struct REN_API CameraAttributes
		{
			glm::vec3 Position;
			glm::vec3 Front;
			glm::vec3 Up;
			glm::vec3 Right;
			glm::vec3 WorldUp;

			float Euler_Yaw;
			float Euler_Pitch;

			float MovementSpeed;
			float MouseSensivitity;

			float Zoom;
		};


		class REN_API Entity
		{
		public:

			Entity() {}

			virtual ~Entity() {}

			virtual void OnUpdate() = 0;

			virtual void EnableObject() = 0;

			virtual void DisableObject() = 0;

			virtual glm::mat4 GetViewMatrix() = 0;

		};
	}
}

