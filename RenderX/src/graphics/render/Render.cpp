#include "graphics/render/Render.h"

namespace renderx {
	namespace graphics {

		Render::Render()
			:m_render(nullptr)
		{
			
		}

		Render::Render(const std::string& vspath, const std::string& fspath)
		{
			
		}

		Render::~Render()
		{
			delete m_render;
		}

		void Render::Draw()
		{
		}

	}
}