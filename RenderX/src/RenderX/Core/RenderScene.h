#pragma once
#include "pch.h"
#include "Material.h"
#include "Model.h"
#include "Shader.h"
#include "ShadowMap.h"
#include "Skybox.h"
#include "../BasicRenderer/BasicRenderer.h"
#include "Transform.h"
#include "../Physics/Collision.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace renderx::Core
{

	
		
	class DirectLight
	{
	public:
		DirectLight() { m_LightPos = glm::vec3(0.0f, 1.0f, 1.0f); }
		glm::vec3 GetLightPos() { return m_LightPos; }
		void Move() { m_LightPos.z = sin(glfwGetTime() * 0.5) * 20.0; }
	private:
		glm::vec3 m_LightPos;

	};


	class PointLight
	{
	public:
		PointLight() { m_LightPos = glm::vec3(0.0f, 1.0f, 1.0f); }
		glm::vec3 GetLightPos() { return m_LightPos; }
		void RenderLight()
		{
			basicRenderer::BasicRenderer::RenderSphere();
		}
	private:
		glm::vec3 m_LightPos;
	};

	


	class RenderScene
	{
	public:
		static std::shared_ptr<RenderScene>& Get();
		static bool& GetSwitchShaderRef();

		void RenderSceneToDepthCubeMap();
		void RenderSceneNormal();

		void SubmitRenderer(const std::string& filePath);
		void RemoveRenderer(const std::string& name);

		void Rendering();
		void Rendering(std::shared_ptr<Shader> shader);

		void DrawSkybox() { m_Skybox->Draw(); }


		std::unordered_map<std::string, Material>& GetRenderersMaterialMapRef() { return m_MaterialMap; }
		std::unordered_map<std::string, Transform>& GetRenderersTransformRef() { return m_TransformMap; }

		std::unordered_map<std::string, std::shared_ptr<Model>>& GetRenderersMapRef() { return m_RenderersMap; }
		std::unordered_map<std::string, int>& GetRendererCountRef() { return m_RendererCount; }
		std::unordered_map<std::string,std::string>& GetRenderersNameInSceneRef() { return m_RenderersNameInScene; }
		std::unordered_map<std::string, BoundingBox>& GetBBoxMapRef() { return m_BBoxMap; }
	private:
		RenderScene();
		static std::shared_ptr<RenderScene> s_Instance;	

		std::unordered_map<std::string, std::shared_ptr<Model>> m_RenderersMap;
		std::unordered_map<std::string, int> m_RendererCount;
		std::unordered_map<std::string,std::string> m_RenderersNameInScene;


		std::shared_ptr<Shader> m_DepthShader;
		ShadowMap m_ShadowMap;
		std::shared_ptr<Skybox> m_Skybox;
		DirectLight m_Light;
		PointLight m_PointLight;

		std::unordered_map<std::string, Material> m_MaterialMap;
		std::unordered_map<std::string, Transform> m_TransformMap;
		std::unordered_map<std::string, BoundingBox> m_BBoxMap;


		float near_plane = 1.0f;
		float far_plane = 25.0f;
		std::vector<glm::mat4> m_ShadowTransforms;


		std::shared_ptr<Shader> m_PbrShader;
		std::shared_ptr<Shader> m_PbrWithTextureShader;

		std::shared_ptr<Shader> m_EquirectangularToCubemapShader;
		std::shared_ptr<Shader> m_IrradianceShader;
		std::shared_ptr<Shader> m_PrefilterShader;
		std::shared_ptr<Shader> m_BrdfShader;

		static bool s_SwitchShader;

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ShadowProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_LightProjectMatrix;
		glm::mat4 m_LightSpaceMatrix;

		static uint32_t s_AlbedoMapDefault;
		static uint32_t s_NormalMapDefault;
		static uint32_t s_MetallicMapDefault;
		static uint32_t s_RoughnessMapDefault;
		static uint32_t s_AOMapDefault;

		

	};
}