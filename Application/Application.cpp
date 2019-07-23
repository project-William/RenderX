#include "Application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>


Application::Application()
{
	m_Window = std::unique_ptr<graphics::Window>(graphics::Window::Create());


	renderLayer = new graphics::RenderLayer(m_Window->GetWinData());
	//
	imgui = new graphics::ImguiLayer(m_Window->GetWinPtr(), m_Window->GetWinData());

	imgui->OnAttach();

	layerList = new graphics::LayerList();
	layerList->PushBackLayer(imgui);
	layerList->PushBackLayer(renderLayer);	
	framebuffer = new graphics::FrameBuffer(m_Window->GetWinWidth(),m_Window->GetWinHeight());

}

Application::~Application()
{
	delete imgui;
	delete renderLayer;
	delete layerList;
}

void Application::Run()
{
	auto& WinData = m_Window->GetWinData();

	while (!m_Window->Closed())
	{	
		//bind framebuffer
		m_Window->Clear();
		framebuffer->BindFrameBuffer();
		framebuffer->UpdateFramebufferTex(m_Window->GetWinWidth(),m_Window->GetWinHeight());
		m_Window->Clear();
		m_Window->ClearColor();
		renderLayer->OnAttach();
		
		//unbind framebuffer
		framebuffer->UnbindFrameBuffer();
		imgui->Begin();
		renderLayer->TestDraw(m_Window->GetWinWidth(), m_Window->GetWinHeight(), framebuffer->GetRendered());
		imgui->OnImguiLayer();


		imgui->End();
		//
		framebuffer->DelFramebufferTex();
		m_Window->OnUpdate();
	}

	imgui->OnDetach();
}














