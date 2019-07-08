#pragma once
#include "..//..//..//Core.h"
#include "..//..//utils/FileUtils.h"


namespace renderx {
	namespace graphics {

		struct REN_API ShaderSource
		{
			std::string vertexSource;
			std::string fragmentSource;
		};

		class REN_API Shader
		{
		private:
			ShaderSource m_Source;
			GLuint m_ShaderProgram;
			const std::string m_VFilePath;
			const std::string m_FFilePath;
		public:
			Shader();
			~Shader();
			Shader(const std::string& vfile, const std::string& ffile);


			void BindShaderProgram() const;
			void UnbindShaderProgram()const;
		private:
			ShaderSource& GetShaderSource();

			GLuint CreateShader(const std::string& file, int type);
			GLuint& CreateShaderProgram();
		};


	}
}