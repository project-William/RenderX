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


			void SetBool(const std::string& name, bool value) const;
			void SetInt(const std::string& name, int value) const;
			void SetFloat(const std::string& name, float value) const;
			void SetVec2(const std::string& name, glm::vec2& value) const;
			void SetVec2(const std::string& name, float x, float y) const;
			void SetVec3(const std::string& name, glm::vec3& value) const;
			void SetVec3(const std::string& name, float x, float y, float z) const;
			void SetVec4(const std::string& name, glm::vec4& value) const;
			void SetVec4(const std::string& name, float x, float y, float z, float w) const;
			void SetMat2(const std::string& name, glm::mat2& mat) const;
			void SetMat3(const std::string& name, glm::mat3& mat) const;
			void SetMat4(const std::string& name, glm::mat4& mat) const;




			void BindShaderProgram() const;
			void UnbindShaderProgram()const;
		private:
			ShaderSource& GetShaderSource();

			GLuint CreateShader(const std::string& file, int type);
			GLuint& CreateShaderProgram();
			void CheckShaderError(const std::string& name, GLuint shader);
		};


	}
}