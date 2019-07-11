#include "graphics/shader/Shader.h"

namespace renderx {
	namespace graphics {

		Shader::Shader()
			:m_VFilePath(), m_FFilePath(), m_ShaderProgram(0)
		{

		}

		Shader::~Shader()
		{

		}

		Shader::Shader(const std::string& vfile, const std::string& ffile)
			:m_VFilePath(vfile),m_FFilePath(ffile),m_ShaderProgram(0)
		{
			m_Source= GetShaderSource();
			m_ShaderProgram = CreateShaderProgram();
		}

		ShaderSource& Shader::GetShaderSource()
		{
			m_Source.vertexSource = utils::FileUtils::read_shader(m_VFilePath);
			m_Source.fragmentSource = utils::FileUtils::read_shader(m_FFilePath);
			return m_Source;
		}

		void Shader::BindShaderProgram()const
		{
			glUseProgram(m_ShaderProgram);
		}

		void Shader::UnbindShaderProgram()const
		{
			glUseProgram(0);
		}


		GLuint Shader::CreateShader(const std::string& file, int type)
		{
			GLuint shader = glCreateShader(type);
			const char* shader_src = file.c_str();
			glShaderSource(shader, 1, &shader_src, NULL);
			glCompileShader(shader);
			CheckShaderError("shader", shader);
			return shader;
		}

		GLuint& Shader::CreateShaderProgram()
		{
			GLuint vertexShader = CreateShader(m_Source.vertexSource, GL_VERTEX_SHADER);
			GLuint fragmentShader = CreateShader(m_Source.fragmentSource, GL_FRAGMENT_SHADER);

			m_ShaderProgram = glCreateProgram();
			std::cout << m_Source.vertexSource << std::endl;
			std::cout << m_Source.fragmentSource << std::endl;
			glAttachShader(m_ShaderProgram, vertexShader);
			glAttachShader(m_ShaderProgram, fragmentShader);
			glLinkProgram(m_ShaderProgram);
			CheckShaderError("program", m_ShaderProgram);
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			return m_ShaderProgram;
		}


		void Shader::CheckShaderError(const std::string& name, GLuint shader)
		{
			if (name == "program")
			{
				int success;
				glGetProgramiv(shader, GL_LINK_STATUS, &success);
				if (!success)
				{
					char infoLog[1024];
					glGetProgramInfoLog(m_ShaderProgram, 1024, NULL, infoLog);
					std::cout << "Error:" << "program:" << infoLog << std::endl;
				}
				else std::cout << "Shader program created successfully!" << std::endl;
			}
			else 
			{
				int success;
				glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
				if (!success)
				{
					char infoLog[1024];
					glGetShaderInfoLog(m_ShaderProgram, 1024, NULL, infoLog);
					std::cout << "Error:" << "program:" << infoLog << std::endl;
				}
				else std::cout << "Shader created successfully!" << std::endl;
			}
		}
	}
}