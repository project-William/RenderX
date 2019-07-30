#include "graphics/render/BasicLight.h"

namespace renderx {
	namespace graphics {

		


		BasicLight::BasicLight(const glm::vec3& position, const glm::vec3& color)
			:m_Position(position),m_LightColor(color)
		{

		}

		BasicLight::~BasicLight()
		{

		}

		void BasicLight::BindObject() const
		{

		}

		void BasicLight::UnbindObject() const
		{
		}

		void BasicLight::Draw(const WinData& windata)
		{
		}

		void BasicLight::RenderProperties()
		{
		}

	}
}