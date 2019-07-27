#pragma once
#include "Entity.h"


namespace renderx {
	namespace entity {

		class REN_API FPSCamera :public Entity
		{
		private:
			CameraAttributes m_CameraAttrib;

		public:
			FPSCamera(glm::vec3 position=glm::vec3(0.0f),
				      glm::vec3 up=glm::vec3(0.0f,1.0f,0.0f),
					  float yaw = YAW,float pitch=PITCH);
			~FPSCamera();

			void OnUpdate() override;
			void EnableObject() override;
			void DisableObject() override;

			inline CameraAttributes GetCameraAttrib()const { return m_CameraAttrib; }


			glm::mat4 GetViewMatrix() override;
			glm::mat4 GetProjectionMatrix();
			glm::mat4 GetModelMatrix();
			

		private:
			void UpdateCameraMatrix();

		};

	}
}