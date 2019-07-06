#pragma once
#include "Shader.h"


namespace renderx {
	namespace graphics {

		class REN_API FragmentShader :public Shader
		{
		private:
			ShaderData m_FragmentShader;
		public:
			FragmentShader()
			{
			}

			FragmentShader(const std::string& filepath)
			{
				m_FragmentShader.filePath = filepath;
				m_FragmentShader.source = utils::FileUtils::read_shader(filepath);
				CreateShader(filepath);
				CompileShader();

			}

			~FragmentShader()
			{
				glDeleteShader(m_FragmentShader.shader);
			}
		protected:

			void CreateShader(const std::string& filepath)
			{
				const char* shadersrc = m_FragmentShader.source.c_str();
				m_FragmentShader.shader = glCreateShader(GL_FRAGMENT_SHADER);
				glShaderSource(m_FragmentShader.shader, 1, &shadersrc, NULL);
				
			}

			void CompileShader()
			{
				glCompileShader(m_FragmentShader.shader);
			}
	
			inline ShaderData GetShaderData()const { return m_FragmentShader; }
		};
	}
}