#pragma once
#include "..//Layer.h"
#include "Render.h"
namespace renderx {
	namespace graphics {

		class REN_API RenderLayer:public Layer
		{
		private:
			Render* m_Render;
		public:
			RenderLayer();
			~RenderLayer();

			void OnAttach() override;
			void OnDetach() override;
			void OnImguiLayer()override;


		};

	}
}