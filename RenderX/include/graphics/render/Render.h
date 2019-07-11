#pragma once
#include "..//VAOVBOEBO/VertexArray.h"
#include "..//shader/Shader.h"
#include "..//VAOVBOEBO/BufferLayout.h"

#include "RenderShape.h"

namespace renderx {
	namespace graphics {

		class REN_API Render
		{
		private:
			RenderObject* m_render;

		public:
			Render();
			~Render();

			void Draw();

		};


	}
}