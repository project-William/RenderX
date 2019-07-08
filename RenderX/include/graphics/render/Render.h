#pragma once
#include "..//VAOVBOEBO/VertexArray.h"
#include "..//shader/Shader.h"

namespace renderx {
	namespace graphics {

		class REN_API Render
		{
		private:
			GLuint m_ShaderProgram;
			Shader* m_Shader;
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