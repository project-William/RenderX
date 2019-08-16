#pragma once
#include "..//..//Core.h"
#include "render/RenderObject.h"
namespace renderx {
	namespace graphics {

		class REN_API HDR
		{
		private:
			std::shared_ptr<Shader> m_HDRShader;
			std::shared_ptr<RenderData> m_RenderData;
		public:
			HDR(const std::string& vfile, const std::string& ffile);
			~HDR();
			
			void EnableHDRProgram(unsigned int& tex);
			void EnableHDR(float exposure);

		};


	}
}