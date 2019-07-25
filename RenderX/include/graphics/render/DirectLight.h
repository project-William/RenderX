#pragma once
#include "RenderLight.h"

namespace renderx {
	namespace graphics {

		class REN_API DirectLight :public RenderLight
		{
		public:
			DirectLight();
			~DirectLight();

		private:
			LightData m_LightData;
		};
	}
}