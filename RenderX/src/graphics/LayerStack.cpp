#include "graphics/LayerList.h"


namespace renderx {
	namespace graphics {

		LayerList::LayerList()
		{

		}

		LayerList::~LayerList()
		{

		}


		void LayerList::PushLayer(Layer* layer)
		{
			m_LayerList.push_back(layer);
		}


		void LayerList::ShowLayer()const
		{
			for (auto& layer : m_LayerList)
				layer->OnImguiLayer();
		}


		void LayerList::PushBackLayer(Layer* layer)
		{
			m_LayerList.push_back(layer);
		}


		void LayerList::PushFrontLayer(Layer* layer)
		{
			m_LayerList.push_front(layer);
		}

	}
}