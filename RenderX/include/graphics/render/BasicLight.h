#pragma once
#include "RenderObject.h"

namespace renderx {
	namespace graphics {

		class REN_API BasicLight:public RenderObject
		{
		public:
			BasicLight(const glm::vec3& position, const glm::vec3& color);
			~BasicLight();

			inline glm::vec3 GetLightPosition()const { return m_Position; }
			inline glm::vec3 GetLightColor()const { return m_LightColor; }


			void BindObject() const override;
			void UnbindObject() const override;
			void Draw(const WinData& windata) override;
			void RenderProperties() override;
			inline Transformation& GetTrans() override { return m_Trans; }
		private:
			glm::vec3 m_Position;
			glm::vec3 m_LightColor;

			Transformation m_Trans;
		};



	}
}