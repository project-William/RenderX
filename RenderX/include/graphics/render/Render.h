#pragma once
#include "..//VAOVBOEBO/VertexArray.h"
#include "..//shader/Shader.h"
#include "..//VAOVBOEBO/BufferLayout.h"
#include "..//render/RenderObject.h"

namespace renderx {
	namespace graphics {

		class REN_API Render
		{
		private:
			RenderObject* m_render;
			RenderObject* m_Renderer;
		public:
			Render();
			Render(const std::string& vspath, const std::string& fspath);
			~Render();

			void Draw();

		};


	}
}