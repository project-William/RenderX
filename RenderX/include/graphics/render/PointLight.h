#pragma once
#include "RenderLight.h"

namespace renderx {
	namespace graphics {

		class REN_API PointLight :public RenderLight
		{
		public:
			PointLight();
			~PointLight();

		private:
			LightData m_LightData;
		};
	}
}