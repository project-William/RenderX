#pragma once
#include "..//..//..//Core.h"	
#include "..//..//utils/FileUtils.h"
#include "..//VAOVBOEBO/VertexArray.h"

namespace renderx {
	namespace graphics {

		class REN_API Render
		{
		private:
			GLuint m_ShaderProgram;
			VertexArray* m_VArray;
			float vertices[9] = {
				-0.5f,-0.5f,0.0f,
				 0.5f,-0.5f,0.0f,
				 0.0f, 0.5f,0.0f,
			};
		public:
			Render();
			~Render();

			void RenderAttrib();

			void use();

			void Build();
			void Draw();

		};


	}
}