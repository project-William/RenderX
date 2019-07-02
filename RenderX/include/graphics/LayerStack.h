#pragma once
#include "..//..//Core.h"
#include "Layer.h"

namespace renderx {
	namespace graphics {

		class REN_API LayerStack
		{
		private:
			std::vector<Layer*> m_LayerStack;


		public:
			LayerStack();
			~LayerStack();

			void ShowLayer() const;
			void PushLayer(Layer* layer);

		};
	}
}