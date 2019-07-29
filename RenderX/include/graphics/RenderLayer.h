#pragma once
#include "Layer.h"
#include "render/RenderCube.h"
#include "FrameBuffer.h"

namespace renderx {
	namespace graphics {

		class REN_API RenderLayer:public Layer
		{
		private:
			std::list<RenderObject*> m_Renderers;
			RenderObject* m_Render;
		public:
			RenderLayer();
			RenderLayer(const WinData& windata);
			~RenderLayer();

			void PushFrontRenderer(RenderObject* renderer);
			void PushBackRenderer(RenderObject* renderer);

			void DoRendering(const WinData& windata);




			void RenderSkybox();
			void RenderShape(const std::string& vspath, const std::string& fspath);
			void RenderModel();
			void OnAttach() override;
			void OnDetach() override;
			void OnImguiLayer() override;

		};

	}
}