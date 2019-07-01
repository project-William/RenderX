#pragma once
#include "..//..//..//Core.h"
#include "..//..//utils/FileUtils.h"

namespace renderx {
	namespace graphics {

		struct ShaderData
		{
			GLuint shader;
			std::string source;
			std::string filePath;
		};

		
		class REN_API Shader
		{
		public:
			Shader(){}
			virtual ~Shader(){}

			virtual inline ShaderData GetShaderData()const = 0;

		};

	}
}