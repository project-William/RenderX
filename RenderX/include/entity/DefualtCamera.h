#pragma once
#include "Entity.h"

namespace renderx {
	namespace entity {

		class REN_API DefaultCamera :public Entity
		{
		public:
			DefaultCamera();
			~DefaultCamera();

			void OnUpdate() override;
			void EnableObject() override;
			void DisableObject() override;

			glm::mat4 GetViewMatrix();
			glm::mat4 GetProjectionMatrix();
			glm::mat4 GetModelMatrix();

		private:
			CameraAttributes m_CameraAttrib;

			//objects that beyond z-Near will not be rendered
			float m_Near;

			//objects that behind z-Far will not be rendered
			float m_Far;

			void ProcessInputMouse();
			void ProcessInputKeyboard();
		private:

		};

	}
}