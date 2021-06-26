#pragma once
#include "pch.h"


namespace renderx::base
{
	class Camera
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
		static std::shared_ptr<Camera>& Get();
		~Camera();

		void EnableInputEvent();
		void OnUpdate();

		//glm::mat4 GetProjectionMatrix(float zoom);
		glm::mat4 GetProjectionMatrix();
		glm::mat4 GetViewMatrix();
		glm::mat4& GetViewMatrixRef() { return m_ViewMatrix; }
		
		void SetViewMatrix();

		CamreaAttrib& GetCameraAttribRef() { return m_CamAttrib; }

		void SetProjectionMatrix(int x,int y);
	private:
		Camera();
		static std::shared_ptr<Camera> s_Instance;
		void ProcessMouseInput();

		void ProcessMouseScrollInput();

		void ProcessKeyboardInput();
		void UpdateCameraPosition();
	private:
		CamreaAttrib m_CamAttrib;
		float m_Distance;

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;

	};

}


