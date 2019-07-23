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
			WinData m_WinData;
		public:
			RenderLayer();
			RenderLayer(WinData& WinData);
			~RenderLayer();


			void TestDraw(const WinData& windata, const GLuint& texture);
			void OnAttach() override;
			void OnDetach() override;
			void OnImguiLayer() override;

		};

	}
}