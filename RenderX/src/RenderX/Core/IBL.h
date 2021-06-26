#pragma once
#include "pch.h"
#include "Shader.h"
#include "Framebuffer.h"

namespace renderx::Core
{
	class IBL
	{
	public:
			
		static std::shared_ptr<IBL>& Get();

		static std::shared_ptr<IBL> Create(FrameBuffer& framebuffer);
		
		
		~IBL() {}

	
		void Init();

		void LoadHDR(const std::string& filePath = "");


		void UpdateLUT();
		void CreateCapture();

		void DeleteCapture();

		void CreateIrrdiance();
		void CreatePrefilter();

		void CreateLUT();

		void ScreenRestore(GLFWwindow* window);

		void SetupIBL(const std::string& filePath);


		std::pair<unsigned int, unsigned int> GetHDRCubeMap() { return m_HDR; }
		unsigned int GetIrrdianceMap() { return m_IrrdianceMap; }
		unsigned int GetPrefilterMap() { return m_PrefilterMap; }
		unsigned int GetBrdfLUTTexture() { return m_BrdfLUTTexture; }
		unsigned int GetColorAttachment() { return m_ColorAttachment; }

		//static FrameBuffer* m_Framebuffer;
		FrameBuffer& m_FramebufferRef;

	private:
		IBL(FrameBuffer& framebuffer) :m_FramebufferRef(framebuffer) {}
		static std::shared_ptr<IBL> s_Instance;

		unsigned int m_IrrdianceMap;
		unsigned int m_PrefilterMap;
		unsigned int m_BrdfLUTTexture;
		unsigned int m_ColorAttachment;
	

		std::pair<unsigned int, unsigned int> m_HDR;

		GLuint m_FBO;
		GLuint m_RBO;

		glm::mat4 m_CaptureProjection;
		glm::mat4 m_CaptureViews[6];


		GLFWwindow* m_Window = nullptr;


		std::shared_ptr<Shader> m_EquiretangularToCubemapShader;
		std::shared_ptr<Shader> m_IrradianceShader;
		std::shared_ptr<Shader> m_PrefilterShader;
		std::shared_ptr<Shader> m_BrdfShader;
		std::shared_ptr<Shader> m_BackgroundShader;



	};
}

