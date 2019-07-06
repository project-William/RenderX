#pragma once

#include "..//Layer.h"
#include "Render.h"
namespace renderx {
	namespace graphics {

		class REN_API RenderLayer :public Layer
		{
		private:
			std::vector<Render*> m_RenderObj;
		public:
			RenderLayer();
			~RenderLayer();

			void OnAttach()override;
			void OnDetach()override;

		};
		
	}
}