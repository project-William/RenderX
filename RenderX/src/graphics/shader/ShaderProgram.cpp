#pragma once
#include "graphics/shader/ShaderProgram.h"


namespace renderx {
	namespace graphics {

		ShaderProgram::ShaderProgram()
			:m_Shader({nullptr,nullptr}),m_ShaderProgram(0)
		{
		}

		ShaderProgram::ShaderProgram(const std::string& v_filepath, const std::string& f_filepath)
		{
			m_ShaderProgram = glCreateProgram();
			m_Shader.first = new VertexShader(v_filepath);
			m_Shader.second = new FragmentShader(f_filepath);

			glAttachShader(m_ShaderProgram, m_Shader.first->GetShaderData().shader);
			glAttachShader(m_ShaderProgram, m_Shader.second->GetShaderData().shader);

			glLinkProgram(m_ShaderProgram);
			glDeleteShader(m_Shader.first->GetShaderData().shader);
			glDeleteShader(m_Shader.second->GetShaderData().shader);

		}

		void ShaderProgram::BindShaderProgram()const
		{
			glUseProgram(m_ShaderProgram);
			delete m_Shader.first;
			delete m_Shader.second;

		}

		void ShaderProgram::UnbindShaderProgram()const
		{
			glUseProgram(0);
		}



	}
}