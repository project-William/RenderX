#include "Application.h"

using namespace Core;

void Application::InitApp()
{
    m_ViewportWin = ui::ViewportWindow::Get();
    
}

void Application::Run()
{

	ui::Imgui::ImguiSetup();
    
    //
    //
    Core::FrameBuffer framebuffer(s_MainWindowInstance->GetWinDataVal().m_Width, s_MainWindowInstance->GetWinDataVal().m_Height);
    
   
    auto hdr=Core::Hdr::Get();
    auto& ibl = Core::IBL::Create(framebuffer);
    //Core::IBL IBL(framebuffer);
    //
    ibl->Init();
    ibl->SetupIBL("resource/textures/hdr/newport_loft.hdr");
   
  


     

	while (!s_MainWindowInstance->Close())
	{

        s_MainWindowInstance->ClearColor(1.0f, 0.2f, 0.2f, 1.0f);
		s_MainWindowInstance->ClearBuffer();
        m_Camera->EnableInputEvent();


        if (base::Window::Get()->GetWindowResizedSignal())
        {
            hdr->UpdateColorAttachment(base::Window::Get()->GetWinDataVal().m_Width, base::Window::Get()->GetWinDataVal().m_Height);
            base::Window::Get()->ResetWindowResizedSignal();
        }
        //lightPos.z =  10.0;
        //ui
        ui::Imgui::ImguiBegin();
        ui::Menubar::RunMenubar();
        
        ////viewport
        ui::Imgui::Run();
        ////environment
        m_ScenePanel->RunSceneHierarchyPanel();
        m_PropEditor->RunPropEditor();
        m_EnvironmentEditor->RunEnvironmentEditor();
        
        m_ViewportWin->RunViewportWindow(framebuffer);
        ui::Imgui::ImguiEnd();
        
        s_RenderScene->RenderSceneToDepthCubeMap();
        
        
   
        //to hdr
        hdr->BindHdrFramebuffer();
        s_RenderScene->RenderSceneNormal();
        s_RenderScene->DrawSkybox();
        hdr->UnbindHdrFramebuffer();
        //
        // 2. render scene as normal 
        // ------------------------
        
        framebuffer.BindFramebuffer();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, ui::ViewportWindow::Get()->GetViewportSize().x, ui::ViewportWindow::Get()->GetViewportSize().y);
        //glViewport(0, 0, base::Window::Get()->GetWindowWidthVal(), base::Window::Get()->GetWindowHeightVal());
        
        hdr->GetShader()->UseShaderProgram();
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, hdr->GetColorAttachment());
        hdr->GetShader()->SetBool("hdr", true);
        hdr->GetShader()->SetFloat("exposure", hdr->GetExposureRef());
        basicRenderer::BasicRenderer::RenderQuad();
        
        
        
        framebuffer.UnbindFramebuffer();
        



        //framebuffer.BindFramebuffer();
        //s_RenderScene->RenderSceneNormal();
        //s_RenderScene->DrawSkybox();
        
        //framebuffer.UnbindFramebuffer();
        


        ///////// 1. render scene into floating point framebuffer
        ///////// -----------------------------------------------
        ///////glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
        ///////glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ///////glm::mat4 projection = glm::perspective(glm::radians(m_Camera->Get()->GetCameraAttribRef().Zoom), (float)base::Window::Get()->GetWinDataVal().m_Width / (float)base::Window::Get()->GetWinDataVal().m_Height, 0.1f, 100.0f);
        ///////glm::mat4 view = m_Camera->Get()->GetViewMatrix();
        ///////glm::mat4 model = glm::mat4(1.0f);
        ///////shader.UseShaderProgram();
        ///////shader.SetMat4("projection", projection);
        ///////shader.SetMat4("view", view);
        ///////glActiveTexture(GL_TEXTURE0);
        ///////glBindTexture(GL_TEXTURE_2D, woodTexture);
        ///////// set lighting uniforms
        ///////for (unsigned int i = 0; i < lightPositions.size(); i++)
        ///////{
        ///////    shader.SetVec3("lights[" + std::to_string(i) + "].Position", lightPositions[i]);
        ///////    shader.SetVec3("lights[" + std::to_string(i) + "].Color", lightColors[i]);
        ///////}
        ///////shader.SetVec3("viewPos", m_Camera->Get()->GetCameraAttribRef().Position);
        ///////// create one large cube that acts as the floor
        ///////model = glm::mat4(1.0f);
        ///////model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0));
        ///////model = glm::scale(model, glm::vec3(12.5f, 0.5f, 12.5f));
        ///////shader.SetMat4("model", model);
        ///////basicRenderer::BasicRenderer::RenderCube();
        ///////// then create multiple cubes as the scenery
        ///////glBindTexture(GL_TEXTURE_2D, containerTexture);
        ///////model = glm::mat4(1.0f);
        ///////model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
        ///////model = glm::scale(model, glm::vec3(0.5f));
        ///////shader.SetMat4("model", model);
        ///////basicRenderer::BasicRenderer::RenderCube();
        ///////
        ///////model = glm::mat4(1.0f);
        ///////model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
        ///////model = glm::scale(model, glm::vec3(0.5f));
        ///////shader.SetMat4("model", model);
        ///////basicRenderer::BasicRenderer::RenderCube();
        ///////
        ///////model = glm::mat4(1.0f);
        ///////model = glm::translate(model, glm::vec3(-1.0f, -1.0f, 2.0));
        ///////model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
        ///////shader.SetMat4("model", model);
        ///////basicRenderer::BasicRenderer::RenderCube();
        ///////
        ///////model = glm::mat4(1.0f);
        ///////model = glm::translate(model, glm::vec3(0.0f, 2.7f, 4.0));
        ///////model = glm::rotate(model, glm::radians(23.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
        ///////model = glm::scale(model, glm::vec3(1.25));
        ///////shader.SetMat4("model", model);
        ///////basicRenderer::BasicRenderer::RenderCube();
        ///////
        ///////model = glm::mat4(1.0f);
        ///////model = glm::translate(model, glm::vec3(-2.0f, 1.0f, -3.0));
        ///////model = glm::rotate(model, glm::radians(124.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
        ///////shader.SetMat4("model", model);
        ///////basicRenderer::BasicRenderer::RenderCube();
        ///////
        ///////model = glm::mat4(1.0f);
        ///////model = glm::translate(model, glm::vec3(-3.0f, 0.0f, 0.0));
        ///////model = glm::scale(model, glm::vec3(0.5f));
        ///////shader.SetMat4("model", model);
        ///////basicRenderer::BasicRenderer::RenderCube();
        ///////
        ///////// finally show all the light sources as bright cubes
        ///////shaderLight.UseShaderProgram();
        ///////shaderLight.SetMat4("projection", projection);
        ///////shaderLight.SetMat4("view", view);
        ///////
        ///////for (unsigned int i = 0; i < lightPositions.size(); i++)
        ///////{
        ///////    model = glm::mat4(1.0f);
        ///////    model = glm::translate(model, glm::vec3(lightPositions[i]));
        ///////    model = glm::scale(model, glm::vec3(0.25f));
        ///////    shaderLight.SetMat4("model", model);
        ///////    shaderLight.SetVec3("lightColor", lightColors[i]);
        ///////    basicRenderer::BasicRenderer::RenderCube();
        ///////}
        ///////glBindFramebuffer(GL_FRAMEBUFFER, 0);
        ///////
        ///////// 2. blur bright fragments with two-pass Gaussian Blur 
        ///////// --------------------------------------------------
        ///////bool horizontal = true, first_iteration = true;
        ///////unsigned int amount = 100;
        ///////shaderBlur.UseShaderProgram();
        ///////for (unsigned int i = 0; i < amount; i++)
        ///////{
        ///////    glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[horizontal]);
        ///////    shaderBlur.SetInt("horizontal", horizontal);
        ///////    glBindTexture(GL_TEXTURE_2D, first_iteration ? colorBuffers[1] : pingpongColorbuffers[!horizontal]);  // bind texture of other framebuffer (or scene if first iteration)
        ///////    basicRenderer::BasicRenderer::RenderQuad();
        ///////    horizontal = !horizontal;
        ///////    if (first_iteration)
        ///////        first_iteration = false;
        ///////}
        ///////glBindFramebuffer(GL_FRAMEBUFFER, 0);
        ///////
        ///////// 3. now render floating point color buffer to 2D quad and tonemap HDR colors to default framebuffer's (clamped) color range
        ///////// --------------------------------------------------------------------------------------------------------------------------
        ///////glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ///////shaderBloomFinal.UseShaderProgram();
        ///////glActiveTexture(GL_TEXTURE0);
        ///////glBindTexture(GL_TEXTURE_2D, colorBuffers[0]);
        ///////glActiveTexture(GL_TEXTURE1);
        ///////glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[!horizontal]);
        ///////shaderBloomFinal.SetInt("bloom", true);
        ///////shaderBloomFinal.SetFloat("exposure", hdr->GetExposureRef());
        ///////basicRenderer::BasicRenderer::RenderQuad();




















		s_MainWindowInstance->OnUpdate();
        


	}

	//ui::Imgui::ImguiBegin();

	//ui::Imgui::Run();
	//ui::Imgui::ImguiDestroy();
}