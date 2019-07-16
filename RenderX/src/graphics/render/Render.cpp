#include "graphics/render/Render.h"

namespace renderx {
	namespace graphics {

		Render::Render()
			:m_render(nullptr)
		{
			m_render = new RenderShape();
		}

		Render::~Render()
		{
			delete m_render;
		}

		void Render::Draw()
		{
			m_render->Draw();
		}

	}
}