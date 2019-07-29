#pragma once
#include "Entity.h"


namespace renderx {
	namespace entity {

		class REN_API FPSCamera :public Entity
		{
		private:
			
		public:
			FPSCamera();
			~FPSCamera();

			void OnUpdate() override;
			void EnableObject() const override;
			void DisableObject() const override;



			glm::mat4 GetViewMatrix();
			glm::mat4 GetProjectionMatrix();
			glm::mat4 GetModelMatrix();
			

		private:
			void UpdateCameraMatrix();

		};

	}
}