#pragma once
#include "..//..//Common.h"
#include "Entity.h"

namespace renderx
{
	namespace entity
	{
		class REN_API Camera:public Entity
		{
		protected:
			struct CamreaAttrib
			{
				glm::vec3 Front;
				glm::vec3 Position;
				glm::vec3 Up;
				glm::vec3 WorldUp;
				glm::vec3 FocusPoint;
				glm::vec3 Right;

				float Yaw;
				float Pitch;
				float Zoom;
			};


		public:
			Camera(const glm::vec3& position);
			~Camera();

			glm::mat4 GetViewMatrix();
			void EnableObject();
			void OnUpdate();
			CamreaAttrib& GetCameraAttribRef() { return m_CamAttrib; }
			glm::mat4 GetProjectionMatrix(float zoom);
		private:
			
			void ProcessMouseInput();

			void ProcessMouseScrollInput();
			
			void ProcessKeyboardInput();
			void UpdateCameraPosition();


		private:			
			CamreaAttrib m_CamAttrib;
			float m_Distance;
		};
	}
}