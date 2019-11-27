#pragma once
#include "..//Common.h"
#include "manager/TextureManager.h"
#include "manager/ShaderManager.h"
#include "manager/RendererManager.h"
#include "entity/Camera.h"
#include "graphics/Framebuffer.h"

namespace renderx
{

	struct REN_API RenderList
	{
		std::string m_Name;
		float m_Roughness;
		float m_Metallic;
		glm::vec4 m_Albedo;
		glm::mat4 m_ModelMat;
		bool m_IsChoose;
	};

	class REN_API Scene
	{

	public:

		static std::shared_ptr<Scene> Create(manager::ShaderManager& sdmanager, manager::TextureManager& texmanager, manager::RendererManager& renmanager);
		~Scene();

		Scene(const Scene&) = delete;
		Scene& operator=(const Scene&) = delete;
		static std::shared_ptr<Scene> GetSceneInstance() { return m_Instance; }


		void SetupIBL(std::shared_ptr<graphics::Framebuffer> framebuffer);
		static void BeginScene();
		void BindPreComputedIBL() const;
		void SetCameraViewport(std::shared_ptr<entity::Camera> cam);
		void RenderScene()const;
		void RenderLights()const;
		void RenderSkybox()const;
		void OnUpdate(bool add);
		static void EndScene();

		uint32_t GetQuadRenderCount()const { return m_QuadRenderCount; }
		uint32_t GetBlockRenderCount()const { return m_BlockRenderCount; }
		uint32_t GetSphereRenderCount()const { return m_SphereRenderCount; }
		uint32_t GetModelRenderCount()const { return m_ModelRenderCount; }
		static uint32_t GetRenderCount() { return s_RenderCount; }

		void AddQuadRenderCount();
		void AddBlockRenderCount();
		void AddSphereRenderCount();
		void AddModelRenderCount();
		void DelSpciRenderInList(const std::string& name);
		void DelQuadRenderCount();
		void DelBlockRenderCount();
		void DelSphereRenderCount();
		void DelModelRenderCount();
		void UpdateRendererRenderCount();

		manager::ShaderManager& GetShaderManager() { return m_ShaderManager; }
		manager::TextureManager& GetTextureManager() { return m_TextureManager; }
		manager::RendererManager& GetRendererManager() { return m_RendererManager; }

		std::list<RenderList>& GetRenderListRef() { return m_RenderList; }
		
	private:
		

		uint32_t m_BlockRenderCount;
		uint32_t m_SphereRenderCount;
		uint32_t m_QuadRenderCount;
		uint32_t m_ModelRenderCount;
		static uint32_t s_RenderCount;


		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;

		std::list<RenderList> m_RenderList;

	private:
		manager::ShaderManager& m_ShaderManager;
		manager::TextureManager& m_TextureManager;
		manager::RendererManager& m_RendererManager;

		static std::shared_ptr<Scene> m_Instance;
		Scene(manager::ShaderManager& sdmanager,manager::TextureManager& texmanager, manager::RendererManager& renmanager);
		
	};
}