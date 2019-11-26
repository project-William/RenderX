#include "Application.h"

 
Application::Application()
{
	m_Test = Test::Create();


	

	
}

Application::~Application()
{

}

void Application::Run()
{

	//SetupIBL();

	m_ShaderManager.SubmitShader(m_BackgroundShader);
	m_ShaderManager.SubmitShader(m_PbrShader);
	m_ShaderManager.SubmitShader(m_PrefilterShader);
	m_ShaderManager.SubmitShader(m_BrdfShader);
	m_ShaderManager.SubmitShader(m_EquirectangularToCubemapShader);
	m_ShaderManager.SubmitShader(m_IrradianceShader);

	m_RendererManager.SubmitRenderer(std::dynamic_pointer_cast<graphics::Renderer>(m_Quad));
	m_RendererManager.SubmitRenderer(std::dynamic_pointer_cast<graphics::Renderer>(m_Sphere));
	m_RendererManager.SubmitRenderer(std::dynamic_pointer_cast<graphics::Renderer>(m_Block));


	m_TextureManager.SubmitTexture(hdrtexture, graphics::TexType::HDR_TEXTURE);
	m_TextureManager.SubmitTexture(cubemap, graphics::TexType::ENVCUBEMAP);
	m_TextureManager.SubmitTexture(brdftexture, graphics::TexType::BRDFLUT_TEXTURE);
	m_TextureManager.SubmitTexture(irradianceMap, graphics::TexType::IRRADIANCEMAP);
	m_TextureManager.SubmitTexture(prefilter, graphics::TexType::PREFILTERMAP);

	m_Scene = Scene::Create(m_ShaderManager, m_TextureManager, m_RendererManager);
	
	m_Scene->SetupIBL(m_Framebuffer);


	// then before rendering, configure the viewport to the original framebuffer's screen dimensions
	m_Window->ConfigFrameSize();
	
	glm::mat4 view;
	glm::mat4 projection;


	//before loop, for gui
	m_Imgui = std::shared_ptr<ui::ImguiWindow>(new ui::ImguiWindow());
	m_SetWin = std::shared_ptr<ui::SettingWindow>(new ui::SettingWindow());
	
	
	graphics::Model ourModel("resources/objects/nanosuit/nanosuit.obj");

	std::shared_ptr<graphics::Shader> sshader(new graphics::Shader("shader/basic.vert", "shader/basic.frag", graphics::ShaderType::BASIC));

	while (!m_Window->Closed())
	{
		utils::Timer timer;
		// per-frame time logic 
		// --------------------
		//float currentFrame = glfwGetTime();
		//deltaTime = currentFrame - lastFrame;
		//lastFrame = currentFrame;

		// render
		// ------
		m_Window->Clear();
		m_Window->ClearColor();

		// render scene, supplying the convoluted irradiance map to the final shader.
		// ------------------------------------------------------------------------------------------
		//m_PbrShader->BindShaderProgram();
		//view = m_Camera->GetViewMatrix();
		//projection = m_Camera->GetProjectionMatrix(m_Camera->GetCameraAttribRef().Zoom);
		//m_PbrShader->SetMat4("view", view);
		//m_PbrShader->SetVec3("camPos", m_Camera->GetCameraAttribRef().Position);
		//m_PbrShader->SetMat4("projection", projection);
		
		// bind pre-computed IBL data
		//manager::TextureManager::BindTexture(m_TextureManager.m_Hdrtexture.GetTexture(), 0, graphics::TexType::IRRADIANCEMAP);
		//manager::TextureManager::BindTexture(m_TextureManager.m_Prefilter.GetTexture(), 1, graphics::TexType::PREFILTERMAP);
		//manager::TextureManager::BindTexture(m_TextureManager.m_Brdftexture.GetTexture(), 2, graphics::TexType::BRDFLUT_TEXTURE);

		// render rows*column number of spheres with material properties defined by textures (they all have the same material properties)
		//glm::mat4 model = glm::mat4(1.0f);
		//for (int32_t row = 0; row < 7; ++row)
		//{
		//	m_Sphere->BindVAO();
		//	m_PbrShader->SetFloat("metallic", (float)row / (float)7);
		//	m_PbrShader->SetVec4("albedo", albedoColor.x, albedoColor.y, albedoColor.z, albedoColor.w);
		//	for (int32_t col = 0; col < 7; ++col)
		//	{
		//		// we clamp the roughness to 0.025 - 1.0 as perfectly smooth surfaces (roughness of 0.0) tend to look a bit off
		//		// on direct lighting.
		//		m_PbrShader->SetFloat("roughness", glm::clamp((float)col / (float)7, 0.05f, 1.0f));
		//
		//		model = glm::mat4(1.0f);
		//		model = glm::translate(model, glm::vec3(
		//			(float)(col - (7 / 2)) * 2.5,
		//			-0.0f,
		//			(float)(row - (7 / 2)) * 2.5
		//		));
		//		m_PbrShader->SetMat4("model", model);
		//		m_Sphere->Draw();
		//	}
		//}

		Scene::BeginScene();
		
		m_Scene->SetCameraViewport(m_Camera);
		m_Scene->BindPreComputedIBL();
		m_Scene->RenderScene();

		sshader->BindShaderProgram();
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
		glm::mat4 view = m_Camera->GetViewMatrix();
		glm::mat4 projection = m_Camera->GetProjectionMatrix(45.0f);
		sshader->SetMat4("model", model);
		sshader->SetMat4("view", view);
		sshader->SetMat4("projection", projection);
		ourModel.Draw(sshader);
		
		// render light source (simply re-render sphere at light positions)
		// this looks a bit off as we use the same shader, but it'll make their positions obvious and 
		// keeps the codeprint small.
		//for (uint32_t i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); ++i)
		//{
		//	glm::vec3 newPos = lightPositions[i] + glm::vec3(sin(glfwGetTime() * 5.0) * 5.0, 0.0, 0.0);
		//	newPos = lightPositions[i];
		//	m_PbrShader->SetVec3("lightPositions[" + std::to_string(i) + "]", newPos);
		//	m_PbrShader->SetVec3("lightColors[" + std::to_string(i) + "]", lightColors[i]);
		//
		//	model = glm::mat4(1.0f);
		//	model = glm::translate(model, newPos);
		//	model = glm::scale(model, glm::vec3(0.5f));
		//	m_PbrShader->SetMat4("model", model);
		//	m_Sphere->BindVAO();
		//	m_Sphere->Draw();
		//
		//}

		// render skybox (render as last to prevent overdraw)
		m_Scene->RenderSkybox();
		Scene::EndScene();
		//m_BackgroundShader->BindShaderProgram();
		//m_BackgroundShader->SetMat4("view", view);
		//m_BackgroundShader->SetMat4("projection", projection);
		//manager::TextureManager::BindTexture(cubemap.GetTexture(), 0, graphics::TexType::ENVCUBEMAP);
		//irradianceMap.BindTexture(0);
		//prefilter.BindTexture(0);
		
		//m_Block->BindVAO();
		//m_Block->Draw();

		// render BRDF map to screen
		//brdfShader.Use();
		//renderQuad();


		//processinput
		m_Camera->EnableObject();

		//render ui
		m_Imgui->UIBegin();
		//graphics setting window
		m_SetWin->Begin();
		m_SetWin->End();
		//m_SetWin->Demo();
		m_SetWin->RendererWindow();
		m_SetWin->AttribWindow(m_Camera);
		m_SetWin->EnvirWindow();
		//m_SetWin->Test();

		//imgui FPS window
		m_SetWin->FPSWindow(timer.GetMilliseconds());

		m_Imgui->UIEnd();

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		m_Window->OnUpdate();
		
	}

	

	//while (m_Running)
	//
	//{
	//	m_Window->Clear();
	//	m_Window->ClearColor();
	//
	//	shader->BindShaderProgram();
	//	m_Sphere->BindVAO();
	//	m_Sphere->Draw();
	//	m_Sphere->SetMVP([&]()
	//	{
	//		view = m_Camera->GetViewMatrix();
	//		projection = glm::perspective(glm::radians(45.0f), (float)m_Window->GetWinWidth() / m_Window->GetWinHeight(), 0.1f, 100.0f);
	//	
	//		shader->SetMat4("model", model);
	//		shader->SetMat4("projection", projection);
	//		shader->SetMat4("view", view);
	//	});
	//	
	//	//m_Sphere->BindVAO();
	//	//m_Sphere->draw();
	//	m_Camera->EnableObject();
	//	m_Window->OnUpdate();
	//}

	

}