#include "graphics/render/BasicLight.h"

namespace renderx {
	namespace graphics {

		BasicLight::BasicLight()
			:m_Position(10.0f,20.0f,10.0f),m_LightColor(1.0f,1.0f,1.0f),m_Shineness(32),m_Direction(-0.2f, -1.0f, -0.3f)
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