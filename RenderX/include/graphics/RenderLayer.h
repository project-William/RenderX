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
			FrameBuffer* m_FrameBuffer;
		public:
			RenderLayer();
			RenderLayer(WinData WinData);
			~RenderLayer();


			inline FrameBuffer* GetFrameBuffer()const { return m_FrameBuffer; }

			void TestDraw(int width, int height);
			void OnAttach() override;
			void OnDetach() override;
			void OnImguiLayer() override;

		};

	}
}