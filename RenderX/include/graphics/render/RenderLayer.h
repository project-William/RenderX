#pragma once
#include "..//Layer.h"

namespace renderx {
	namespace graphics {

		class REN_API RenderLayer:public Layer
		{
		private:

		public:
			RenderLayer();
			~RenderLayer();

			void OnAttach() override;
			void OnDetach() override;
			void OnUpdate() override;
			void OnImguiLayer()override;


		};

	}
}