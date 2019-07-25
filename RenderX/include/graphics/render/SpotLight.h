#pragma once
#include "RenderLight.h"
namespace renderx {
	namespace graphics {

		class REN_API SpotLight :public RenderLight
		{
		public:
			SpotLight();
			~SpotLight();

		private:
			LightData m_LightData;

		};
	}
}