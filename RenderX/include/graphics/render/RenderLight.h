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
			
		};


	}
}