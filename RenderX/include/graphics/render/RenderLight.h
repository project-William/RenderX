#pragma once
#include "RenderObject.h"

namespace renderx {
	namespace graphics {
		
		struct REN_API LightData
		{
			glm::vec3 L_Position;
		};


		
		class REN_API RenderLight :public RenderObject
		{
		public:
			RenderLight() {}
			virtual ~RenderLight() {}

			virtual void BindObject() const override {}
			virtual void UnbindObject() const override {}
			virtual void Draw(const WinData& windata) override {}
			virtual void RenderProperties() override {}
			virtual void Position(const glm::vec3& position) override {}
			virtual void Rotation(const float radians, const glm::vec3& axis) override {}
			virtual void Scale(const float scale) override {}
		};


	}
}