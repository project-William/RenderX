#include "graphics/render/BasicLight.h"

namespace renderx {
	namespace graphics {

		BasicLight::BasicLight()
			:m_Position(3.0f,3.0f,3.0f),m_LightColor(1.0f,1.0f,1.0f),m_Shineness(32)
		{

		}


		BasicLight::BasicLight(const glm::vec3& position, const glm::vec3& color)
			:m_Position(position.x,-position.y,position.z),m_LightColor(color),m_Shineness(32)
		{

		}

		BasicLight::~BasicLight()
		{

		}

	}
}