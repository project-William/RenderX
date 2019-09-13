#include "graphics/EnvFramebuffer.h"
#include "graphics/texture/stb_image.h"

namespace renderx {
	namespace graphics {

		EnvFramebuffer::EnvFramebuffer()
		{

			equirectangularToCubemapShader=new Shader("shader/toCubemap.vert", "shader/toCubemap.frag");
			backgroundShader = new Shader("shader/backvertex.vert", "shader/backfragment.frag");
			backgroundShader->BindShaderProgram();
			backgroundShader->SetInt("environmentMap", 0);

			glGenFramebuffers(1, &m_EnvFBO);
			glBindFramebuffer(GL_FRAMEBUFFER, m_EnvFBO);

			glBindRenderbuffer(GL_RENDERBUFFER, m_EnvRBO);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 1200, 800);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_EnvRBO);

			stbi_set_flip_vertically_on_load(true);
			int width, height, nrComponents;
			float* data = stbi_loadf("texture/ibl_hdr_radiance.hdr", &width, &height, &nrComponents, 0);
			if (data)
			{
				glGenTextures(1, &hdrTexture);
				glBindTexture(GL_TEXTURE_2D, hdrTexture);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, data); // note how we specify the texture's data value to be float

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				stbi_image_free(data);
			}
			else
			{
				std::cout << "Failed to load HDR image." << std::endl;
			}
			
			glGenTextures(1, &envCubemap);
			glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
			for (unsigned int i = 0; i < 6; ++i)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 1200, 800, 0, GL_RGB, GL_FLOAT, nullptr);
			}
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			
			equirectangularToCubemapShader->BindShaderProgram();
			equirectangularToCubemapShader->SetInt("equirectangularMap", 0);
			equirectangularToCubemapShader->SetMat4("projection", captureProjection);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, hdrTexture);

			glViewport(0, 0, 1200, 800); // don't forget to configure the viewport to the capture dimensions.
			glBindFramebuffer(GL_FRAMEBUFFER, m_EnvFBO);
			for (unsigned int i = 0; i < 6; ++i)
			{
				equirectangularToCubemapShader->SetMat4("view", captureViews[i]);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, envCubemap, 0);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				renderCube();
			}
			glBindFramebuffer(GL_FRAMEBUFFER, 0);

			glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)1200/ (float)800, 0.1f, 100.0f);
			backgroundShader->BindShaderProgram();
			backgroundShader->SetMat4("projection", projection);

;
		}

		EnvFramebuffer::~EnvFramebuffer()
		{

		}


	}
}