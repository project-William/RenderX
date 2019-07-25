#pragma once
#include "RenderObject.h"

namespace renderx {
	namespace graphics {

		class REN_API RenderSkybox:public RenderObject
		{
		public:
			RenderSkybox();
			~RenderSkybox();

			void BindObject() const override;
			void UnbindObject() const override;
			void Draw(const WinData& windata) override;
			void RenderProperties() override;
		private:
			void Position(const glm::vec3& position) override;
			void Rotation(const float radians, const glm::vec3& axis) override;
			void Scale(const float scale) override;


		};
	}
}