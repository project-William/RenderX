#include "pch.h"	
#include "IBL.h"
#include "Texture.h"
#include "../BasicRenderer/BasicRenderer.h"
#include "Framebuffer.h"
#include "../Base/Window.h"


namespace renderx::Core
{
	std::shared_ptr<IBL> IBL::s_Instance;

	std::shared_ptr<IBL> IBL::Create(FrameBuffer& framebuffer)
	{
		if (!s_Instance)
		{
			s_Instance = std::shared_ptr<IBL>(new IBL(framebuffer));
		}

		return s_Instance;
	}

	std::shared_ptr<IBL>& IBL::Get()
	{
		if (!s_Instance)
		{
			throw std::exception("need to create IBL firstly!");
		}

		return s_Instance;
	}
	


	
	void IBL::Init()
	{
		
		m_EquiretangularToCubemapShader = std::shared_ptr<Shader>(new Shader("shaderSource/cubemap.vert", "shaderSource/equirectangular_to_cubemap.frag"));
		m_IrradianceShader = std::shared_ptr<Shader>(new Shader("shaderSource/cubemap.vert", "shaderSource/irradiance_convolution.frag"));
		m_PrefilterShader = std::shared_ptr<Shader>(new Shader("shaderSource/cubemap.vert", "shaderSource/prefilter.frag"));
		m_BrdfShader = std::shared_ptr<Shader>(new Shader("shaderSource/brdf.vert", "shaderSource/brdf.frag"));


		m_FramebufferRef.SetupFramebuffer();
		//glGenFramebuffers(1, &m_FBO);
		//glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
		//
		//glGenRenderbuffers(1, &m_RBO);
		//glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
		//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, base::Window::Get()->GetWinDataVal().m_Width, base::Window::Get()->GetWinDataVal().m_Height);
		//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_RBO);
		//m_Framebuffer = new FrameBuffer();
		//m_Framebuffer->SetupFramebuffer(base::Window::Get()->GetWinDataVal().m_Width, base::Window::Get()->GetWinDataVal().m_Height);
		
		// pbr: set up projection and view matrices for capturing data onto the 6 cubemap face directions
		// ----------------------------------------------------------------------------------------------
		m_CaptureProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
		m_CaptureViews[0] = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
		m_CaptureViews[1] = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
		m_CaptureViews[2] = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		m_CaptureViews[3] = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
		m_CaptureViews[4] = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f));
		m_CaptureViews[5]= glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f));
		

	}


	void IBL::LoadHDR(const std::string& filePath)
	{
		m_HDR = Core::TextureLoader::LoadEnvMap(filePath);

		// pbr: convert HDR equirectangular environment map to cubemap equivalent
		// ----------------------------------------------------------------------
		m_EquiretangularToCubemapShader->UseShaderProgram();
		m_EquiretangularToCubemapShader->SetInt("equirectangularMap", 0);
		m_EquiretangularToCubemapShader->SetMat4("projection", m_CaptureProjection);
		TextureLoader::UseTexture(0, m_HDR.first, TextureType::TEXTURE2D);

		glViewport(0, 0, 512, 512); // don't forget to configure the viewport to the capture dimensions.
		//glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
		m_FramebufferRef.BindFramebuffer();
		for (unsigned int i = 0; i < 6; ++i)
		{
			m_EquiretangularToCubemapShader->SetMat4("view", m_CaptureViews[i]);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, m_HDR.second, 0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			basicRenderer::BasicRenderer::RenderCube();
		}
		//glBindFramebuffer(GL_FRAMEBUFFER, 0);

		m_FramebufferRef.UnbindFramebuffer();

		// then let OpenGL generate mipmaps from first mip face (combatting visible dots artifact)
		TextureLoader::UseTexture(0, m_HDR.second, TextureType::TEXTURE_CUBE);
		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	}

	void IBL::UpdateLUT()
	{
		m_FramebufferRef.BindFramebuffer();
		m_FramebufferRef.BindRenderbuffer();
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_BrdfLUTTexture, 0);
		//FrameBuffer::SetFramebufferTexture2D(0, m_BrdfLUTTexture, TextureType::TEXTURE2D, 0);

		glViewport(0, 0, 512, 512);
		m_BrdfShader->UseShaderProgram();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		basicRenderer::BasicRenderer::RenderQuad();

		//glBindFramebuffer(GL_FRAMEBUFFER, 0);

		m_FramebufferRef.UnbindFramebuffer();
	}

	void IBL::CreateCapture()
	{

	}

	void IBL::DeleteCapture()
	{
	}

	void IBL::CreateIrrdiance()
	{
		// pbr: create an irradiance cubemap, and re-scale capture FBO to irradiance scale.
	// --------------------------------------------------------------------------------
		glGenTextures(1, &m_IrrdianceMap);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_IrrdianceMap);
		for (unsigned int i = 0; i < 6; ++i)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 32, 32, 0, GL_RGB, GL_FLOAT, nullptr);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
		//glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
		m_FramebufferRef.BindFramebuffer();
		m_FramebufferRef.BindRenderbuffer();
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 32, 32);

		// pbr: solve diffuse integral by convolution to create an irradiance (cube)map.
		// -----------------------------------------------------------------------------
		m_IrradianceShader->UseShaderProgram();
		m_IrradianceShader->SetInt("environmentMap", 0);
		m_IrradianceShader->SetMat4("projection", m_CaptureProjection);
		TextureLoader::UseTexture(0, m_HDR.second, TextureType::TEXTURE_CUBE);

		glViewport(0, 0, 32, 32); // don't forget to configure the viewport to the capture dimensions.
		//glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
		m_FramebufferRef.BindFramebuffer();
		//m_Framebuffer->BindFramebuffer();
		for (unsigned int i = 0; i < 6; ++i)
		{
			m_IrradianceShader->SetMat4("view", m_CaptureViews[i]);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, m_IrrdianceMap, 0);
			//FrameBuffer::SetFramebufferTexture2D(i, m_IrrdianceMap, TextureType::TEXTURE_CUBE, 0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			basicRenderer::BasicRenderer::RenderCube();
		}
		//glBindFramebuffer(GL_FRAMEBUFFER, 0);

		m_FramebufferRef.UnbindFramebuffer();
	}

	void IBL::CreatePrefilter()
	{
		// pbr: create a pre-filter cubemap, and re-scale capture FBO to pre-filter scale.
	// --------------------------------------------------------------------------------
		glGenTextures(1, &m_PrefilterMap);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_PrefilterMap);
		for (unsigned int i = 0; i < 6; ++i)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 128, 128, 0, GL_RGB, GL_FLOAT, nullptr);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // be sure to set minifcation filter to mip_linear 
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// generate mipmaps for the cubemap so OpenGL automatically allocates the required memory.
		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

		// pbr: run a quasi monte-carlo simulation on the environment lighting to create a prefilter (cube)map.
		// ----------------------------------------------------------------------------------------------------
		m_PrefilterShader->UseShaderProgram();
		m_PrefilterShader->SetInt("environmentMap", 0);
		m_PrefilterShader->SetMat4("projection", m_CaptureProjection);
		TextureLoader::UseTexture(0, m_HDR.second, TextureType::TEXTURE_CUBE);

		//glBindFramebuffer(GL_FRAMEBUFFER, m_CaptureFBO);
		//glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
		m_FramebufferRef.BindFramebuffer();
		
		unsigned int maxMipLevels = 5;
		for (unsigned int mip = 0; mip < maxMipLevels; ++mip)
		{
			// reisze framebuffer according to mip-level size.
			unsigned int mipWidth = 128 * std::pow(0.5, mip);
			unsigned int mipHeight = 128 * std::pow(0.5, mip);
			//glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
			m_FramebufferRef.BindFramebuffer();

			//m_Framebuffer->BindRenderbuffer();
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, mipWidth, mipHeight);
			glViewport(0, 0, mipWidth, mipHeight);

			float roughness = (float)mip / (float)(maxMipLevels - 1);
			m_PrefilterShader->SetFloat("roughness", roughness);
			for (unsigned int i = 0; i < 6; ++i)
			{
				m_PrefilterShader->SetMat4("view", m_CaptureViews[i]);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, m_PrefilterMap, mip);
				//FrameBuffer::SetFramebufferTexture2D(i, m_PrefilterMap, TextureType::TEXTURE_CUBE, mip);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				basicRenderer::BasicRenderer::RenderCube();

			}
		}
		//glBindFramebuffer(GL_FRAMEBUFFER, 0);

		m_FramebufferRef.UnbindFramebuffer();
	}

	void IBL::CreateLUT()
	{
		// pbr: generate a 2D LUT from the BRDF equations used.
	// ----------------------------------------------------
		glGenTextures(1, &m_BrdfLUTTexture);

		// pre-allocate enough memory for the LUT texture.
		glBindTexture(GL_TEXTURE_2D, m_BrdfLUTTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RG16F, 512, 512, 0, GL_RG, GL_FLOAT, 0);
		// be sure to set wrapping mode to GL_CLAMP_TO_EDGE
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// then re-configure capture framebuffer object and render screen-space quad with BRDF shader.
		//glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
		//glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
		m_FramebufferRef.BindFramebuffer();
		m_FramebufferRef.BindRenderbuffer();
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_BrdfLUTTexture, 0);
		//FrameBuffer::SetFramebufferTexture2D(0, m_BrdfLUTTexture, TextureType::TEXTURE2D, 0);

		glViewport(0, 0, 512, 512);
		m_BrdfShader->UseShaderProgram();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		basicRenderer::BasicRenderer::RenderQuad();

		//glBindFramebuffer(GL_FRAMEBUFFER, 0);

		m_FramebufferRef.UnbindFramebuffer();
	}

	void IBL::SetupIBL(const std::string& filePath)
	{
		LoadHDR(filePath);
		CreateIrrdiance();
		CreatePrefilter();
		CreateLUT();
	}


	void IBL::ScreenRestore(GLFWwindow* window)
	{
	}
}