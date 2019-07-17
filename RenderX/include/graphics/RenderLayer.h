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
			FrameBuffer* m_FrameBuffer;
		public:
			RenderLayer();
			RenderLayer(WinPros winPros);
			~RenderLayer();


			inline FrameBuffer* GetFrameBuffer()const { return m_FrameBuffer; }

			void TestDraw();
			void OnAttach() override;
			void OnDetach() override;
			void OnImguiLayer() override;

		};

	}
}