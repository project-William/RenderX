#include "graphics/LayerStack.h"


namespace renderx {
	namespace graphics {

		LayerStack::LayerStack()
		{

		}

		LayerStack::~LayerStack()
		{

		}


		void LayerStack::PushLayer(Layer* layer)
		{
			m_LayerStack.push_back(layer);
		}


		void LayerStack::ShowLayer()const
		{
			for (auto& layer : m_LayerStack)
				layer->OnImguiLayer();
		}
	}
}