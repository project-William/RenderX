#pragma once
#include "..//Common.h"
#include "entity/Camera.h"
#include "graphics/Shader.h"

namespace renderx
{
	class REN_API Test
	{
	private:
		Test() {}
		static std::shared_ptr<Test> m_Instance;
		
		unsigned int quadVAO = 0;
		unsigned int quadVBO;
		unsigned int cubeVAO = 0;
		unsigned int cubeVBO = 0;
		unsigned int sphereVAO = 0;
		unsigned int indexCount;
	public:


		


		// lights
		// ------
		glm::vec3 lightPositions[4] = {
			glm::vec3(-10.0f,  10.0f, 10.0f),
			glm::vec3(10.0f,  10.0f, 10.0f),
			glm::vec3(-10.0f, -10.0f, 10.0f),
			glm::vec3(10.0f, -10.0f, 10.0f),
		};
		glm::vec3 lightColors[4] = {
			glm::vec3(300.0f, 300.0f, 300.0f),
			glm::vec3(300.0f, 300.0f, 300.0f),
			glm::vec3(300.0f, 300.0f, 300.0f),
			glm::vec3(300.0f, 300.0f, 300.0f)
		};
		int nrRows = 7;
		int nrColumns = 7;
		float spacing = 2.5;


		unsigned int hdrTexture = 0;
		unsigned int envCubemap;
		unsigned int irradianceMap;
		unsigned int prefilterMap;
		unsigned int brdfLUTTexture;


		glm::mat4 captureProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
		glm::mat4 captureViews[6] =
		{
			glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
			glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
			glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
			glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
			glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
			glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
		};


		void HdrTexture();
		void EnvMap();
		void GererateMipmap(unsigned int cubemap);
		void IrrdianceMap();
		void BindEnvMap(unsigned int cubemap);
		void Prefilter();
		void BRDF();
		void equ(std::shared_ptr<graphics::Shader> equ, unsigned int hdr);

		void BindIrrdianceMap(int slot, unsigned int irrdiance)
		{
			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(GL_TEXTURE_CUBE_MAP, irrdiance);
		}
		
		void BindPrefilterMap(int slot, unsigned int prefilter)
		{
			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(GL_TEXTURE_CUBE_MAP, prefilter);
		}
		
		void BindBRDFmap(int slot, unsigned int brdf)
		{
			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(GL_TEXTURE_2D, brdf);
		}

		
		~Test() {}

		void renderQuad();
		void renderCube();
		static std::shared_ptr<Test> Create();

		std::shared_ptr<Test> GetInstance()
		{
			return m_Instance;
		}

		void fbo(std::shared_ptr<entity::Camera> cam,
			std::shared_ptr<graphics::Shader> pbr,
			std::shared_ptr<graphics::Shader> equ,
			std::shared_ptr<graphics::Shader> irr,
			std::shared_ptr<graphics::Shader> pre,
			std::shared_ptr<graphics::Shader> brd,
			std::shared_ptr<graphics::Shader> bac,
			std::function<void()> func1,
			unsigned int fbo, unsigned int rbo
		);



		void renderSphere();
		
	};
}