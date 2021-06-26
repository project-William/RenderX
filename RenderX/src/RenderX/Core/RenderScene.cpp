#pragma once
#include "pch.h"
#include "RenderScene.h"
#include "../Editor/ViewportWindow.h"
#include "../Base/Camera.h"
#include "IBL.h"
#include "../Utils/FileDialogs.h"
#include "../BasicRenderer/BasicRenderer.h"
#include "../Base/Window.h"


namespace renderx::Core
{
	uint32_t RenderScene::s_AlbedoMapDefault;
	uint32_t RenderScene::s_NormalMapDefault;
	uint32_t RenderScene::s_MetallicMapDefault;
	uint32_t RenderScene::s_RoughnessMapDefault;
	uint32_t RenderScene::s_AOMapDefault;


	std::shared_ptr<RenderScene> RenderScene::s_Instance;
	bool RenderScene::s_SwitchShader = true;

	bool& RenderScene::GetSwitchShaderRef()
	{
		return s_SwitchShader;
	}

	RenderScene::RenderScene()
	{
		s_AlbedoMapDefault = TextureLoader::LoadTexture("resource/textures/pbr/board/albedo.png", true);
		s_NormalMapDefault = TextureLoader::LoadTexture("resource/textures/pbr/board/normal.png", true);
		s_MetallicMapDefault = TextureLoader::LoadTexture("resource/textures/pbr/board/metallic.png", true);
		s_RoughnessMapDefault = TextureLoader::LoadTexture("resource/textures/pbr/board/roughness.png", true);
		s_AOMapDefault = TextureLoader::LoadTexture("resource/textures/pbr/board/ao.png", true);

		m_Skybox = Skybox::Get();


		m_PbrShader = std::shared_ptr<Shader>(new Shader("shaderSource/pbr.vert", "shaderSource/pbr.frag"));
		m_PbrWithTextureShader = std::shared_ptr<Shader>(new Shader("shaderSource/pbr.vert", "shaderSource/pbrWithTexture.frag"));
		//m_DepthShader = std::shared_ptr<Shader>(new Shader("shaderSource/point_shadows_depth.vert", "shaderSource/point_shadows_depth.frag", "shaderSource/point_shadows_depth.geom"));
		m_ShadowMap.Init();

		m_PbrShader->UseShaderProgram();
		m_PbrShader->SetInt("irradianceMap", 0);
		m_PbrShader->SetInt("prefilterMap", 1);
		m_PbrShader->SetInt("brdfLUT", 2);
		m_PbrShader->SetInt("depthMap", 8);
		m_PbrShader->SetInt("pointDepthMap", 9);
		m_PbrShader->SetVec3("albedo", 1.0f, 1.0f, 1.0f);
		m_PbrShader->SetFloat("ao", 1.0f);
		m_PbrShader->SetFloat("u_roughness", 0.0f);
		m_PbrShader->SetFloat("u_metallic", 1.0f);

		m_PbrShader->SetVec3("pointLightPos", 0.0f, 10.0f, 0.0f);

		m_PbrWithTextureShader->UseShaderProgram();
		m_PbrWithTextureShader->SetInt("irradianceMap", 0);
		m_PbrWithTextureShader->SetInt("prefilterMap", 1);
		m_PbrWithTextureShader->SetInt("brdfLUT", 2);
		m_PbrWithTextureShader->SetInt("albedoMap", 3);
		m_PbrWithTextureShader->SetInt("normalMap", 4);
		m_PbrWithTextureShader->SetInt("metallicMap", 5);
		m_PbrWithTextureShader->SetInt("roughnessMap", 6);
		m_PbrWithTextureShader->SetInt("aoMap", 7);
		m_PbrWithTextureShader->SetInt("depthMap", 8);
		m_PbrWithTextureShader->SetInt("pointDepthMap", 9);
		m_PbrWithTextureShader->SetFloat("u_roughness", 1.0f);
		m_PbrWithTextureShader->SetFloat("u_metallic", 1.0f);
		m_PbrWithTextureShader->SetVec3("pointLightPos", 0.0f, 10.0f, 0.0f);

		m_ProjectionMatrix = glm::perspective(glm::radians(base::Camera::Get()->GetCameraAttribRef().Zoom), (float)ui::ViewportWindow::Get()->GetViewportSize().x / (float)ui::ViewportWindow::Get()->GetViewportSize().y, 0.1f, 100.0f);
		m_PbrShader->UseShaderProgram();
		m_PbrShader->SetMat4("projection", m_ProjectionMatrix);
		m_PbrWithTextureShader->UseShaderProgram();
		m_PbrWithTextureShader->SetMat4("projection", m_ProjectionMatrix);

		for (int i = 0; i < 6; i++)
		{
			m_ShadowTransforms.push_back(glm::mat4(1.0f));
		}

		SubmitRenderer("D:\\github\\my\\RenderX\\Application\\resource\\board.obj");
		auto& model = m_TransformMap["board_0"].ModelMatrix;
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
		SubmitRenderer("D:\\github\\my\\RenderX\\Application\\resource\\cube.obj");
	}

	std::shared_ptr<RenderScene>& RenderScene::Get()
	{
		if (!s_Instance)
		{
			s_Instance = std::shared_ptr<RenderScene>(new RenderScene());
		}
		return s_Instance;
	}

	void RenderScene::RenderSceneToDepthCubeMap()
	{


		glViewport(0, 0, m_ShadowMap.GetShadowWidth(), m_ShadowMap.GetShadowHeight());
		glBindFramebuffer(GL_FRAMEBUFFER, m_ShadowMap.GetDepthFBO());
		glClear(GL_DEPTH_BUFFER_BIT);
		m_LightProjectMatrix = glm::ortho(-50.0f, 50.0f, -50.0f, 50.0f, -10.0f, 50.0f);
		m_ViewMatrix = glm::lookAt(m_Light.GetLightPos(), glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
		m_LightSpaceMatrix = m_LightProjectMatrix * m_ViewMatrix;
		// render scene from light's point of view
		m_ShadowMap.GetDepthShader()->UseShaderProgram();
		m_ShadowMap.GetDepthShader()->SetMat4("lightSpaceMatrix", m_LightSpaceMatrix);
		m_ShadowMap.GetDepthShader()->SetMat4("model", glm::mat4(1.0f));
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, woodTexture);
		//basicRenderer::BasicRenderer::renderScene(*m_ShadowMap.GetDepthShader());
		
		
		Rendering(m_ShadowMap.GetDepthShader());
		
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		

		glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), (float)1024 / (float)1024, near_plane, far_plane);
		std::vector<glm::mat4> shadowTransforms;
		glm::vec3 lightPos(0.0f,10.0f,0.0f);
		shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
		shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
		shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
		shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
		shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
		shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));

		glViewport(0, 0, 1024, 1024);
		glBindFramebuffer(GL_FRAMEBUFFER, m_ShadowMap.GetPointDepthFBO());
		glClear(GL_DEPTH_BUFFER_BIT);
		m_ShadowMap.GetPointDepthShader()->UseShaderProgram();
		for (unsigned int i = 0; i < 6; ++i)
			m_ShadowMap.GetPointDepthShader()->SetMat4("shadowMatrices[" + std::to_string(i) + "]", shadowTransforms[i]);
		m_ShadowMap.GetPointDepthShader()->SetFloat("far_plane", far_plane);
		m_ShadowMap.GetPointDepthShader()->SetVec3("lightPos", 0.0f, 10.0f,0.0f);
		Rendering(m_ShadowMap.GetPointDepthShader());
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}

	


	void RenderScene::RenderSceneNormal()
	{
		//m_Light.Move();
		//glViewport(0, 0, ui::ViewportWindow::Get()->GetViewportSize().x, ui::ViewportWindow::Get()->GetViewportSize().y);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, base::Window::Get()->GetWinDataVal().m_Width, base::Window::Get()->GetWinDataVal().m_Height);
		glDepthFunc(GL_LEQUAL);
		// enable seamless cubemap sampling for lower mip levels in the pre-filter map.
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
		m_ViewMatrix = base::Camera::Get()->GetViewMatrix();
		base::Camera::Get()->SetProjectionMatrix(ui::ViewportWindow::Get()->GetViewportSize().x, ui::ViewportWindow::Get()->GetViewportSize().y);

		

	

		

		Rendering();

	}


	void RenderScene::SubmitRenderer(const std::string& filePath)
	{
		std::string rawName = utils::FileDialogs::GetFileName(filePath);

		if (rawName != "")
		{
			Material material;
			Transform transform;
			std::string newName;

			material.albedoMap = s_AlbedoMapDefault;
			material.aoMap = s_AOMapDefault;
			material.metallicMap = s_MetallicMapDefault;
			material.normalMap = s_NormalMapDefault;
			material.roughnessMap = s_RoughnessMapDefault;

			if (m_RenderersMap.find(rawName) == m_RenderersMap.end())
			{
				//rawName += "_" + std::to_string(m_RendererCount[rawName]);
				
				std::shared_ptr<Model> model(new Model(filePath));
				m_RenderersMap.insert({ rawName, model});
				m_RendererCount[rawName] = 0;
				newName = rawName + "_0";
				m_RenderersNameInScene.insert({ newName, rawName });
				m_MaterialMap.insert({ newName,material });
				m_TransformMap.insert({ newName,transform });
				m_BBoxMap.insert({ newName,model->m_AABB });
			}
			else
			{
				m_RendererCount[rawName]++;
				std::string newName = rawName + "_" + std::to_string(m_RendererCount[rawName]);
				
				m_RenderersNameInScene.insert({ newName, rawName });
				m_MaterialMap.insert({ newName,material });
				m_TransformMap.insert({ newName,transform});
				m_BBoxMap.insert({ newName,m_RenderersMap[rawName]->m_AABB });

			}
		}
	}

	void RenderScene::RemoveRenderer(const std::string& name)
	{
		std::string raw = utils::FileDialogs::GetRawNameOfRenderer(name);
		m_RendererCount[raw]--;
		m_RenderersNameInScene.erase(name);
		m_MaterialMap.erase(name);
		m_TransformMap.erase(name);
		m_BBoxMap.erase(name);
		if (m_RendererCount[raw]==-1)
		{
			m_RenderersMap.erase(raw);
			m_RendererCount.erase(raw);
		}

	}



	void RenderScene::Rendering()
	{
	
		

		for (auto iter = m_RenderersNameInScene.begin(); iter != m_RenderersNameInScene.end(); iter++)
		{
			auto newName = iter->first;
			auto rawName = iter->second;
			auto& modelMatrix = m_TransformMap[newName].ModelMatrix;
			auto& material = m_MaterialMap[newName];

			if (material.switchShader ==ShaderType::PBR_COLOR)
			{
				m_PbrShader->UseShaderProgram();
				m_PbrShader->SetMat4("view", m_ViewMatrix);
				m_PbrShader->SetMat4("projection", base::Camera::Get()->GetProjectionMatrix());
				m_PbrShader->SetVec3("camPos", base::Camera::Get()->GetCameraAttribRef().Position);
				m_PbrShader->SetVec3("lightPos", m_Light.GetLightPos());
				m_PbrShader->SetVec3("pointLightPos", 0.0f, 10.0f, 0.0f);
				m_PbrShader->SetFloat("far_plane", far_plane);
				m_PbrShader->SetMat4("lightSpaceMatrix", m_LightSpaceMatrix);

				m_PbrShader->SetMat4("model", modelMatrix);
				m_PbrShader->SetFloat("u_roughness", material.roughness);
				m_PbrShader->SetFloat("u_metallic", material.metallic);
				m_PbrShader->SetVec3("albedo", material.color);
			}
			else if (material.switchShader == ShaderType::PBR_TEXTURE)
			{
				m_PbrWithTextureShader->UseShaderProgram();
				m_PbrWithTextureShader->SetMat4("view", m_ViewMatrix);
				m_PbrWithTextureShader->SetMat4("projection", base::Camera::Get()->GetProjectionMatrix());
				m_PbrWithTextureShader->SetVec3("camPos", base::Camera::Get()->GetCameraAttribRef().Position);
				m_PbrWithTextureShader->SetVec3("pointLightPos", 0.0f, 10.0f, 0.0f);
				m_PbrWithTextureShader->SetVec3("lightPos", m_Light.GetLightPos());
				m_PbrWithTextureShader->SetFloat("far_plane", far_plane);
				m_PbrWithTextureShader->SetMat4("lightSpaceMatrix", m_LightSpaceMatrix);



				m_PbrWithTextureShader->SetMat4("model", modelMatrix);
				m_PbrWithTextureShader->SetFloat("u_roughness", material.roughness);
				m_PbrWithTextureShader->SetFloat("u_metallic", material.metallic);
				m_PbrWithTextureShader->SetVec3("albedo", material.color);
			}
		
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, IBL::Get()->GetIrrdianceMap());
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_CUBE_MAP, IBL::Get()->GetPrefilterMap());
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, IBL::Get()->GetBrdfLUTTexture());
			glActiveTexture(GL_TEXTURE8);
			glBindTexture(GL_TEXTURE_2D, m_ShadowMap.GetDepthMap());
			glActiveTexture(GL_TEXTURE9);
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_ShadowMap.GetPointDepthMap());
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, material.albedoMap);
			glActiveTexture(GL_TEXTURE4);
			glBindTexture(GL_TEXTURE_2D, material.normalMap);
			glActiveTexture(GL_TEXTURE5);
			glBindTexture(GL_TEXTURE_2D, material.metallicMap);
			glActiveTexture(GL_TEXTURE6);
			glBindTexture(GL_TEXTURE_2D, material.roughnessMap);
			glActiveTexture(GL_TEXTURE7);
			glBindTexture(GL_TEXTURE_2D, material.aoMap);


			m_RenderersMap[rawName]->Draw();

		}

	}


	void RenderScene::Rendering(std::shared_ptr<Shader> shader)
	{

		for (auto iter = m_RenderersNameInScene.begin(); iter != m_RenderersNameInScene.end(); iter++)
		{
			auto newName = iter->first;
			auto rawName = iter->second;
			auto& modelMatrix = m_TransformMap[newName].ModelMatrix;
			auto& material = m_MaterialMap[newName];

			
			shader->SetMat4("model", modelMatrix);
			shader->SetFloat("u_roughness",material.roughness);
			shader->SetFloat("u_metallic", material.metallic);
			shader->SetVec3("albedo", material.color);

			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, material.albedoMap);
			glActiveTexture(GL_TEXTURE4);
			glBindTexture(GL_TEXTURE_2D, material.normalMap);
			glActiveTexture(GL_TEXTURE5);
			glBindTexture(GL_TEXTURE_2D, material.metallicMap);
			glActiveTexture(GL_TEXTURE6);
			glBindTexture(GL_TEXTURE_2D, material.roughnessMap);
			glActiveTexture(GL_TEXTURE7);
			glBindTexture(GL_TEXTURE_2D, material.aoMap);


			m_RenderersMap[rawName]->Draw();

		}


		physics::Collision col;
		col.TestCollision();

	}
}