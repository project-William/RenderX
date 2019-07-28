#pragma once
#pragma once
#include "..//Core.h"

namespace renderx {
	namespace entity {

		
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
			glm::vec3 Position = glm::vec3(0.0f);
			glm::vec3 Front = glm::vec3(0.0f);
			glm::vec3 Up = glm::vec3(0.0f);
			glm::vec3 Right = glm::vec3(0.0f);
			glm::vec3 WorldUp = glm::vec3(0.0f);

			float Euler_Yaw = 0;
			float Euler_Pitch = 0;

			float MovementSpeed = 0;
			float MouseSensivitity = 0;

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


		};
	}
}

