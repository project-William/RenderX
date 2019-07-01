#pragma once
#include "Shader.h"

namespace renderx {
	namespace graphics {
		

		class REN_API VertexShader :public Shader
		{
		private:
			ShaderData m_VertexShader;
		public:
			VertexShader()
			{
			}

			VertexShader(const std::string& filepath)
			{
				m_VertexShader.filePath = filepath;
				m_VertexShader.source = utils::FileUtils::read_shader(filepath);
				std::cout << m_VertexShader.source << std::endl;
				CreateShader(filepath);
				CompileShader();
			}

			~VertexShader()
			{
				glDeleteShader(m_VertexShader.shader);
			}

			inline ShaderData GetShaderData()const { return m_VertexShader; }


		protected:
			void CreateShader(const std::string& filepath)
			{
				const char* shadersrc = m_VertexShader.source.c_str();
				m_VertexShader.shader = glCreateShader(GL_VERTEX_SHADER);
				glShaderSource(m_VertexShader.shader, 1, &shadersrc, NULL);

			}
			void CompileShader()
			{
				glCompileShader(m_VertexShader.shader);
			}

		};
	}
}