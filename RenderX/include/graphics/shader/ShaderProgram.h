#pragma once
#include "FragmentShader.h"
#include "VertexShader.h"


namespace renderx {
	namespace graphics {

		
		class REN_API ShaderProgram
		{
		private:
			std::pair<Shader*, Shader*> m_Shader;
			GLuint m_ShaderProgram;
		public:
			ShaderProgram();
			~ShaderProgram();
			ShaderProgram(const std::string& v_filepath, const std::string& f_filepath);

			void BindShaderProgram() const;
			void UnbindShaderProgram() const;

		};
	}
}