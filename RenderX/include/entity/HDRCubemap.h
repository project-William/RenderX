#pragma once
#include "Entity.h"
#include "..//graphics/texture/HDRTexture.h"
#include "..//graphics/texture/CubemapTexture.h"
#include "..//graphics/render/RenderObject.h"

namespace renderx {
	using CamPair = std::pair<entity::FPSCamera*, entity::MayaCamera*>;

	namespace entity {

		class REN_API HDRCubemap :public Entity
		{
		public:
			HDRCubemap(const std::string& filepath, const std::string& vsfile, const std::string& ffile);
			~HDRCubemap();

			inline GLuint& GetHDRTextureRef() { return m_Cubemap->GetHDRTextureRef(); }
			inline GLuint GetHDRTextureVal()const { return m_Cubemap->GetHDRTextureVal(); }
			inline std::shared_ptr<graphics::RenderData>& GetRenderDataRef() { return m_RenderData; }

			void UseHDRTexture();
			void RenderSkybox(CamPair& camera);
			void EnableObject() override;
			void DisableObject() override;
			void OnUpdate() override;
			void RenderCube();

			glm::mat4& GetCaptureProjection() { return m_CaptureProjection; }
			std::vector<glm::mat4>& GetCaptureViews() { return m_CaptureViews; }
			GLuint GetEnvCubemap() { return envCubemap; }
			void Init();

			graphics::CubemapTexture* GetCubemap() { return m_EnvCubemap; }
		private:
			unsigned int envCubemap;
			graphics::CubemapTexture* m_EnvCubemap;
			std::shared_ptr<graphics::RenderData> m_RenderData;
			std::shared_ptr<graphics::RenderData> m_RenderData1;
			std::shared_ptr<graphics::HDRTexture> m_Cubemap;

			glm::mat4 m_CaptureProjection = glm::perspective(glm::radians(90.0f), 12.0f/8, 0.1f, 100.0f);
			std::vector<glm::mat4> m_CaptureViews =
			{
				glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
				glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
				glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
				glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
				glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
				glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
			};


			std::vector<float> m_CubeData =
			{
				// positions         // texture coords // normals           
				-1.0f, -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,  0.0f, -1.0f,
				 1.0f, -1.0f, -1.0f, 1.0f,  0.0f, 0.0f,  0.0f, -1.0f,
				 1.0f,  1.0f, -1.0f, 1.0f,  1.0f, 0.0f,  0.0f, -1.0f,
				 1.0f,  1.0f, -1.0f, 1.0f,  1.0f, 0.0f,  0.0f, -1.0f,
				-1.0f,  1.0f, -1.0f, 0.0f,  1.0f, 0.0f,  0.0f, -1.0f,
				-1.0f, -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,  0.0f, -1.0f,

				-1.0f, -1.0f,  1.0f, 0.0f,  0.0f, 0.0f,  0.0f,  1.0f,
				 1.0f, -1.0f,  1.0f, 1.0f,  0.0f, 0.0f,  0.0f,  1.0f,
				 1.0f,  1.0f,  1.0f, 1.0f,  1.0f, 0.0f,  0.0f,  1.0f,
				 1.0f,  1.0f,  1.0f, 1.0f,  1.0f, 0.0f,  0.0f,  1.0f,
				-1.0f,  1.0f,  1.0f, 0.0f,  1.0f, 0.0f,  0.0f,  1.0f,
				-1.0f, -1.0f,  1.0f, 0.0f,  0.0f, 0.0f,  0.0f,  1.0f,

				-1.0f,  1.0f,  1.0f, 1.0f,  0.0f, 1.0f,  0.0f,  0.0f,
				-1.0f,  1.0f, -1.0f, 1.0f,  1.0f, 1.0f,  0.0f,  0.0f,
				-1.0f, -1.0f, -1.0f, 0.0f,  1.0f, 1.0f,  0.0f,  0.0f,
				-1.0f, -1.0f, -1.0f, 0.0f,  1.0f, 1.0f,  0.0f,  0.0f,
				-1.0f, -1.0f,  1.0f, 0.0f,  0.0f, 1.0f,  0.0f,  0.0f,
				-1.0f,  1.0f,  1.0f, 1.0f,  0.0f, 1.0f,  0.0f,  0.0f,

				 1.0f,  1.0f,  1.0f, 1.0f,  0.0f, 1.0f,  0.0f,  0.0f,
				 1.0f,  1.0f, -1.0f, 1.0f,  1.0f, 1.0f,  0.0f,  0.0f,
				 1.0f, -1.0f, -1.0f, 0.0f,  1.0f, 1.0f,  0.0f,  0.0f,
				 1.0f, -1.0f, -1.0f, 0.0f,  1.0f, 1.0f,  0.0f,  0.0f,
				 1.0f, -1.0f,  1.0f, 0.0f,  0.0f, 1.0f,  0.0f,  0.0f,
				 1.0f,  1.0f,  1.0f, 1.0f,  0.0f, 1.0f,  0.0f,  0.0f,

				-1.0f, -1.0f, -1.0f, 0.0f,  1.0f, 0.0f, -1.0f,  0.0f,
				 1.0f, -1.0f, -1.0f, 1.0f,  1.0f, 0.0f, -1.0f,  0.0f,
				 1.0f, -1.0f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,  0.0f,
				 1.0f, -1.0f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,  0.0f,
				-1.0f, -1.0f,  1.0f, 0.0f,  0.0f, 0.0f, -1.0f,  0.0f,
				-1.0f, -1.0f, -1.0f, 0.0f,  1.0f, 0.0f, -1.0f,  0.0f,

				-1.0f,  1.0f, -1.0f, 0.0f,  1.0f, 0.0f,  1.0f,  0.0f,
				 1.0f,  1.0f, -1.0f, 1.0f,  1.0f, 0.0f,  1.0f,  0.0f,
				 1.0f,  1.0f,  1.0f, 1.0f,  0.0f, 0.0f,  1.0f,  0.0f,
				 1.0f,  1.0f,  1.0f, 1.0f,  0.0f, 0.0f,  1.0f,  0.0f,
				-1.0f,  1.0f,  1.0f, 0.0f,  0.0f, 0.0f,  1.0f,  0.0f,
				-1.0f,  1.0f, -1.0f, 0.0f,  1.0f, 0.0f,  1.0f,  0.0f,
			};
		};

	}
}