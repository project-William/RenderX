#include "graphics/shader/Shader.h"

namespace renderx {
	namespace graphics {

		Shader::Shader()
		{

		}

		Shader::~Shader()
		{

		}

		Shader::Shader(const std::string& vfile, const std::string& ffile)
			:m_VFilePath(vfile),m_FFilePath(ffile)
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
			return shader;
		}

		GLuint& Shader::CreateShaderProgram()
		{
			GLuint vertexShader = CreateShader(m_VFilePath, GL_VERTEX_SHADER);
			GLuint fragmentShader = CreateShader(m_FFilePath, GL_FRAGMENT_SHADER);
			std::cout << vertexShader << std::endl;
			std::cout << fragmentShader << std::endl;
			m_ShaderProgram = glCreateProgram();
			std::cout << m_Source.vertexSource << std::endl;
			std::cout << m_Source.fragmentSource << std::endl;
			glAttachShader(m_ShaderProgram, vertexShader);
			glAttachShader(m_ShaderProgram, fragmentShader);
			glLinkProgram(m_ShaderProgram);
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			return m_ShaderProgram;
		}
	}
}