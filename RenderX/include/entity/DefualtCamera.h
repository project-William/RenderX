#pragma once
#include "Entity.h"

namespace renderx {
	namespace entity {

		class REN_API DefaultCamera :public Entity
		{
		private:

		public:
			DefaultCamera();
			~DefaultCamera();

			void OnUpdate() override;
			void EnableObject() override;
			void DisableObject() override;

			glm::mat4 GetViewMatrix() override;
			glm::mat4 GetProjectionMatrix();
			glm::mat4 GetModelMatrix();


		};

	}
}