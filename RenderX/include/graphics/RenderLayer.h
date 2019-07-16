#pragma once
#include "Layer.h"
#include "render/Render.h"
#include "FrameBuffer.h"

namespace renderx {
	namespace graphics {


		class REN_API RenderLayer:public Layer
		{
		private:
			Render* m_Render;
			WinPros m_WinData;
		public:
			RenderLayer();
			RenderLayer(WinPros winPros);
			~RenderLayer();

			
			void OnAttach() override;
			void OnDetach() override;
			void OnImguiLayer()override;


		};

	}
}