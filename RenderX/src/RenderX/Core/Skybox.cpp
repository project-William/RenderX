#include "pch.h"
#include "Skybox.h"
#include "../BasicRenderer/BasicRenderer.h"
#include "../Base/Camera.h"
#include "../Base/Window.h"
#include "IBL.h"
#include "../Editor/ViewportWindow.h"

namespace renderx::Core
{
	std::shared_ptr<Skybox> Skybox::s_Instance;

	std::shared_ptr<Skybox>& Skybox::Get()
	{
		if (!s_Instance)
		{
			s_Instance = std::shared_ptr<Skybox>(new Skybox());
		}

		return s_Instance;
	}



	Skybox::Skybox()
		:m_IsUseIrridiance(false), m_IsUseSkybox(true)
	{
		m_SkyboxShader = std::shared_ptr<Shader>(new Shader("shaderSource/background.vert", "shaderSource/background.frag"));
		m_SkyboxShader->UseShaderProgram();
		m_SkyboxShader->SetInt("environmentMap", 0);

	}
	Skybox::~Skybox()
	{
		
	}

	void Skybox::Draw()
	{
		if (m_IsUseSkybox)
		{
			//glDisable(GL_CULL_FACE);

			m_SkyboxShader->UseShaderProgram();
			m_SkyboxShader->SetInt("environmentMap", 0);
			m_SkyboxShader->SetMat4("projection", glm::perspective(glm::radians(base::Camera::Get()->GetCameraAttribRef().Zoom), (float)ui::ViewportWindow::Get()->GetViewportSize().x / (float)ui::ViewportWindow::Get()->GetViewportSize().y, 0.1f, 100.0f));
			//m_SkyboxShader->SetMat4("projection", glm::perspective(glm::radians(base::Camera::Get()->GetCameraAttribRef().Zoom), (float)base::Window::Get()->GetWinDataVal().m_Width/ (float)base::Window::Get()->GetWinDataVal().m_Height, 0.1f, 100.0f));

			m_SkyboxShader->SetMat4("view", base::Camera::Get()->GetViewMatrix());

			if (m_IsUseIrridiance)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_CUBE_MAP, IBL::Get()->GetIrrdianceMap());
			}
			else 
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_CUBE_MAP, IBL::Get()->GetHDRCubeMap().second);
			}

			basicRenderer::BasicRenderer::RenderCube();
		}
		
	}


	void Skybox::DrawUseIrrdiance()
	{
		if (m_IsUseIrridiance)
		{
			//glDisable(GL_CULL_FACE);
			m_SkyboxShader->UseShaderProgram();
			m_SkyboxShader->SetMat4("projection", glm::perspective(glm::radians(base::Camera::Get()->GetCameraAttribRef().Zoom), (float)ui::ViewportWindow::Get()->GetViewportSize().x / (float)ui::ViewportWindow::Get()->GetViewportSize().y, 0.1f, 100.0f));

			m_SkyboxShader->SetMat4("view", base::Camera::Get()->GetViewMatrix());
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, IBL::Get()->GetIrrdianceMap());
			basicRenderer::BasicRenderer::RenderCube();
		}
	}

}