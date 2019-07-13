#pragma once
#include "..//..//Core.h"
#include "Layer.h"

namespace renderx {
	namespace graphics {

		class REN_API LayerList
		{
		private:
			std::list<Layer*> m_LayerList;

		public:
			LayerList();
			~LayerList();

			inline const std::list<Layer*> GetLayerList()const { return m_LayerList; }

			void RenderLayers() const;
		
			void PushBackLayer(Layer* layer);
			void PushFrontLayer(Layer* layer);


		};
	}
}