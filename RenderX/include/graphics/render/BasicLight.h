#pragma once
#include "RenderLight.h"

namespace renderx {
	namespace graphics {

		class REN_API BasicLight:public RenderLight
		{
		public:
			BasicLight();
			BasicLight(const glm::vec3& position, const glm::vec3& color);
			~BasicLight();

			inline glm::vec3 GetLightPosition()const override { return m_Position; }
			inline glm::vec3 GetLightColor()const override { return m_LightColor; }
			inline float GetShineness()const override { return m_Shineness; }
			inline float& GetShinenessRef() override { return m_Shineness; }
			inline glm::vec3& GetLightPositionRef() override { return m_Position; }
			inline glm::vec3& GetLightColorRef()override { return m_LightColor; }

			inline glm::vec3& GetLightDirectionRef()override { return m_Direction; }
			



		private:
			glm::vec3 m_Position;
			glm::vec3 m_LightColor;
			glm::vec3 m_Direction;
			float m_Shineness;
		};



	}
}