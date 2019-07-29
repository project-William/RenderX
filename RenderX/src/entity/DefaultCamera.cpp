#include "entity/DefualtCamera.h"

namespace renderx {
	namespace entity {
		
		DefaultCamera::DefaultCamera()
		{

		}
		
		DefaultCamera::~DefaultCamera()
		{

		}

		void DefaultCamera::OnUpdate()
		{

		}

		void DefaultCamera::EnableObject() const 
		{

		}

		void DefaultCamera::DisableObject() const
		{

		}

		

		glm::mat4 DefaultCamera::GetViewMatrix()
		{
			return glm::mat4();
		}

		glm::mat4 DefaultCamera::GetProjectionMatrix()
		{
			return glm::mat4();
		}

		glm::mat4 DefaultCamera::GetModelMatrix()
		{
			return glm::mat4();
		}


	}
}