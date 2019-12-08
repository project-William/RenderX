#include "Scene.h"
#include "Window.h"
#include "graphics/render/Block.h"

namespace renderx
{
	std::shared_ptr<Scene> Scene::m_Instance = nullptr;

	uint32_t Scene::s_RenderCount = 0;

	Scene::Scene(manager::ShaderManager& sdmanager, manager::TextureManager& texmanager, manager::RendererManager& renmanager)
		:m_ShaderManager(sdmanager),
		m_TextureManager(texmanager),
		m_RendererManager(renmanager),
		m_BlockRenderCount(1),
		m_SphereRenderCount(1),
		m_QuadRenderCount(1),
		m_ModelRenderCount(0)
	{
		s_RenderCount = m_BlockRenderCount + m_SphereRenderCount + m_ModelRenderCount + m_QuadRenderCount;
		view = glm::mat4(1.0f);
		projection = glm::mat4(1.0f);
		model = glm::mat4(1.0f);

		for (size_t i = 0; i < s_RenderCount; i++)
		{
			//name, metallic , roughness , albedo , model matrix  
			m_RenderList.push_back({ m_RendererManager.GetRendererVecRef()[i]->GetName()+"1",0.0f,0.0f,glm::vec4(1.0f),model, false });
			model = glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f));
		}
	}

	Scene::~Scene()
	{
	}

	std::shared_ptr<Scene> Scene::Create(manager::ShaderManager& sdmanager, manager::TextureManager& texmanager, manager::RendererManager& renmanager)
	{
		if (!m_Instance)
		{
			m_Instance = std::shared_ptr<Scene>(new Scene(sdmanager,texmanager,renmanager));
			return m_Instance;
		}
		return m_Instance;
	}

	void Scene::BeginScene()
	{
	}

	void Scene::BindPreComputedIBL() const
	{
		manager::TextureManager::BindTexture(m_TextureManager.GetIrrdiTexture().GetTexture(), 0, graphics::TexType::IRRADIANCEMAP);
		manager::TextureManager::BindTexture(m_TextureManager.GetPrefTexture().GetTexture(), 1, graphics::TexType::PREFILTERMAP);
		manager::TextureManager::BindTexture(m_TextureManager.GetBRDFTexture().GetTexture(), 2, graphics::TexType::BRDFLUT_TEXTURE);
	}

	void Scene::SetCameraViewport(std::shared_ptr<entity::Camera> cam)
	{
		m_ShaderManager.GetPBRShaderRef()->BindShaderProgram();
		view = cam->GetViewMatrix();
		projection = cam->GetProjectionMatrix(cam->GetCameraAttribRef().Zoom);
		m_ShaderManager.GetPBRShaderRef()->SetMat4("view", view);
		m_ShaderManager.GetPBRShaderRef()->SetMat4("projection", projection);
		m_ShaderManager.GetPBRShaderRef()->SetVec3("camPos", cam->GetCameraAttribRef().Position);
	}

	void Scene::RenderScene()const
	{
		size_t rendererIndex = 3;

		for (auto& iter : m_RenderList)
		{
			m_ShaderManager.GetPBRShaderRef()->SetMat4("model", iter.m_ModelMat);
			m_ShaderManager.GetPBRShaderRef()->SetVec4("albedo", iter.m_Albedo);
			m_ShaderManager.GetPBRShaderRef()->SetFloat("metallic", iter.m_Metallic);
			m_ShaderManager.GetPBRShaderRef()->SetFloat("roughness", iter.m_Roughness);


			if (iter.m_Name.substr(0,5) == "Block")
			{
				m_RendererManager.GetBasicShapeBlockPtr()->BindVAO();
				m_RendererManager.GetBasicShapeBlockPtr()->Draw();
			}
			else if (iter.m_Name.substr(0,6) == "Sphere")
			{
				m_RendererManager.GetBasicShapeSpherePtr()->BindVAO();
				m_RendererManager.GetBasicShapeSpherePtr()->Draw();
			}
			else if (iter.m_Name.substr(0,4) == "Quad")
			{
				m_RendererManager.GetBasicShapeQuadPtr()->BindVAO();
				m_RendererManager.GetBasicShapeQuadPtr()->Draw();
			}
			else
			{
				m_RendererManager.GetRendererVecRef()[rendererIndex]->BindVAO();
				m_RendererManager.GetRendererVecRef()[rendererIndex]->Draw();
				rendererIndex++;
			}
			
		}

	}

	void Scene::RenderLights()const
	{

	}

	void Scene::RenderSkybox()const
	{
		m_ShaderManager.GetBackgroundShaderRef()->BindShaderProgram();
		m_ShaderManager.GetBackgroundShaderRef()->SetMat4("view", view);
		m_ShaderManager.GetBackgroundShaderRef()->SetMat4("projection", projection);

		manager::TextureManager::BindTexture(m_TextureManager.GetCubeMAP().GetTexture(), 0, graphics::TexType::ENVCUBEMAP);
		//irradianceMap.BindTexture(0);
		//prefilter.BindTexture(0);
		m_RendererManager.GetBasicShapeBlockPtr()->BindVAO();
		m_RendererManager.GetBasicShapeBlockPtr()->Draw();
	}

	void Scene::SetupIBL(std::shared_ptr<graphics::Framebuffer> framebuffer)
	{
		auto win = Window::GetWindowInstance();
		framebuffer->SetupFramebuffer();

		m_ShaderManager.GetCubemapShaderRef()->BindShaderProgram();
		m_ShaderManager.GetCubemapShaderRef()->SetInt("equirectangularMap", 0);
		m_ShaderManager.GetCubemapShaderRef()->SetMat4("projection", graphics::Texture::captureProjection);

		manager::TextureManager::BindTexture(m_TextureManager.GetHDRTexture().GetTexture(), 0, graphics::TexType::HDR_TEXTURE);
		win->ConfigViewport(512, 512);
		framebuffer->BindFramebuffer();
		for (size_t i = 0; i < 6; i++)
		{
			m_ShaderManager.GetCubemapShaderRef()->SetMat4("view", graphics::Texture::captureViews[i]);
			framebuffer->FramebufferTexture2D(m_TextureManager.GetCubeMAP().GetTexture(), i, 0);
			win->Clear();
			m_RendererManager.GetBasicShapeBlockPtr()->BindVAO();
			m_RendererManager.GetBasicShapeBlockPtr()->Draw();
		}
		framebuffer->UnbindFramebuffer();
		graphics::Texture::GenerateMipMap(m_TextureManager.GetCubeMAP().GetTexture());

		framebuffer->BindFramebuffer();
		framebuffer->BindRenderbuffer();
		framebuffer->RenderbufferStorage(32, 32);

		// br:solve diffuse integral by convolution to create an irradiance (cube)map.
		m_ShaderManager.GetIrrdianceShaderRef()->BindShaderProgram();
		m_ShaderManager.GetIrrdianceShaderRef()->SetInt("environmentMap", 0);
		m_ShaderManager.GetIrrdianceShaderRef()->SetMat4("projection", graphics::Texture::captureProjection);


		manager::TextureManager::BindTexture(m_TextureManager.GetCubeMAP().GetTexture(), 0, graphics::TexType::ENVCUBEMAP);
		win->ConfigViewport(32, 32);
		framebuffer->BindFramebuffer();

		for (size_t i = 0; i < 6; ++i)
		{
			m_ShaderManager.GetIrrdianceShaderRef()->SetMat4("view", graphics::Texture::captureViews[i]);
			framebuffer->FramebufferTexture2D(m_TextureManager.GetIrrdiTexture().GetTexture(), i, 0);
			win->Clear();
			m_RendererManager.GetBasicShapeBlockPtr()->BindVAO();
			m_RendererManager.GetBasicShapeBlockPtr()->Draw();
		}
		framebuffer->UnbindFramebuffer();

		m_ShaderManager.GetPrefilterShaderRef()->BindShaderProgram();
		m_ShaderManager.GetPrefilterShaderRef()->SetInt("environmentMap", 0);
		m_ShaderManager.GetPrefilterShaderRef()->SetMat4("projection", graphics::Texture::captureProjection);

		manager::TextureManager::BindTexture(m_TextureManager.GetCubeMAP().GetTexture(), 0, graphics::TexType::ENVCUBEMAP);
		framebuffer->BindFramebuffer();

		int32_t maxMipLevels = 5;
		for (unsigned int mip = 0; mip < maxMipLevels; ++mip)
		{
			// reisze framebuffer according to mip-level size.
			int32_t mipWidth = 128 * std::pow(0.5, mip);
			int32_t mipHeight = 128 * std::pow(0.5, mip);
			framebuffer->BindRenderbuffer();
			framebuffer->RenderbufferStorage(mipWidth, mipHeight);
			win->ConfigViewport(mipWidth, mipHeight);

			float roughness = static_cast<float>(mip) / static_cast<float>(maxMipLevels - 1);
			m_ShaderManager.GetPrefilterShaderRef()->SetFloat("roughness", roughness);
			for (int32_t i = 0; i < 6; ++i)
			{
				m_ShaderManager.GetPrefilterShaderRef()->SetMat4("view", graphics::Texture::captureViews[i]);
				framebuffer->FramebufferTexture2D(m_TextureManager.GetPrefTexture().GetTexture(), i, mip);
				win->Clear();
				m_RendererManager.GetBasicShapeBlockPtr()->BindVAO();
				m_RendererManager.GetBasicShapeBlockPtr()->Draw();
			}
		}
		framebuffer->UnbindFramebuffer();

		framebuffer->BindFramebuffer();
		framebuffer->BindRenderbuffer();
		framebuffer->RenderbufferStorage(512, 512);
		framebuffer->FramebufferTexture2D(m_TextureManager.GetBRDFTexture().GetTexture(), 0);

		win->ConfigViewport(512, 512);
		m_ShaderManager.GetBRDFShaderRef()->BindShaderProgram();
		win->Clear();
		m_RendererManager.GetBasicShapeQuadPtr()->BindVAO();
		m_RendererManager.GetBasicShapeQuadPtr()->Draw();

		framebuffer->UnbindFramebuffer();
	}

	void Scene::OnUpdate(bool add)
	{
		
	}

	void Scene::AddQuadRenderCount()
	{
		m_QuadRenderCount++;
		UpdateRendererRenderCount();
		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(1.0f * (s_RenderCount) , 0.0f, 0.0f));
		m_RenderList.push_back({ "Quad"+ std::to_string(m_QuadRenderCount),0.0f,0.0f,glm::vec4(1.0f), model ,false});
	}

	void Scene::AddBlockRenderCount()
	{
		m_BlockRenderCount++;
		UpdateRendererRenderCount();
		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(1.0f * (s_RenderCount), 0.0f, 0.0f));
		m_RenderList.push_back({ "Block" + std::to_string(m_BlockRenderCount),0.0f,0.0f,glm::vec4(1.0f), model, false });
	}

	void Scene::AddSphereRenderCount()
	{
		m_SphereRenderCount++;
		UpdateRendererRenderCount();
		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(1.0f * (s_RenderCount), 0.0f, 0.0f));
		m_RenderList.push_back({ "Sphere" + std::to_string(m_SphereRenderCount),0.0f,0.0f,glm::vec4(1.0f),model, false });
	}

	void Scene::AddModelRenderCount()
	{
		m_ModelRenderCount++;
		UpdateRendererRenderCount();
		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(1.0f * (s_RenderCount), 0.0f, 0.0f));
		m_RenderList.push_back({ "Model" + std::to_string(m_ModelRenderCount),0.0f,0.0f,glm::vec4(1.0f),model, false });
	}

	void Scene::DelSpciRenderInList(const std::string& name)
	{
		for (auto iter = m_RenderList.rbegin(); iter != m_RenderList.rend(); ++iter)
		{
			if (iter->m_Name.find(name) != std::string::npos)
			{
				m_RenderList.erase(--iter.base()); break;
			}
		}
	}

	void Scene::DelQuadRenderCount()
	{
		if (m_QuadRenderCount > 0)
		{
			m_QuadRenderCount--;
			UpdateRendererRenderCount();
			DelSpciRenderInList("Quad");
		}
	}

	void Scene::DelBlockRenderCount()
	{
		if (m_BlockRenderCount > 0)
		{
			m_BlockRenderCount--;
			UpdateRendererRenderCount();
			DelSpciRenderInList("Block");
		}
	}

	void Scene::DelSphereRenderCount()
	{
		if (m_SphereRenderCount > 0)
		{
			m_SphereRenderCount--;
			UpdateRendererRenderCount();
			DelSpciRenderInList("Sphere");
		}
	}

	void Scene::DelModelRenderCount()
	{
		if (m_ModelRenderCount > 0)
		{
			m_ModelRenderCount--;
			UpdateRendererRenderCount();
			DelSpciRenderInList("Model");
		}
	}

	void Scene::UpdateRendererRenderCount()
	{
		s_RenderCount = m_BlockRenderCount + m_SphereRenderCount + m_ModelRenderCount + m_QuadRenderCount;
	}
	
	void Scene::EndScene()
	{

	}
}