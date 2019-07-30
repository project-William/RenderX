#pragma once
#include "Layer.h"


namespace renderx {
	namespace graphics {

		class REN_API EntityLayer :public Layer
		{
		public:
			EntityLayer();
			~EntityLayer();

			void OnAttach() override;
			void OnDetach() override;
			void OnImguiLayer() override;

		};



	}
}