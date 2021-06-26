#include "pch.h"

namespace renderx::Core
{
	struct Transform
	{
		glm::mat4 ModelMatrix = glm::mat4(1.0f);
		glm::vec3 Translation = glm::vec3(1.0f);
		glm::vec3 Rotation = glm::vec3(0.0f);
		glm::vec3 Scale = glm::vec3(1.0f);
	};
}