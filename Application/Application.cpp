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
	framebuffer = new graphics::FrameBuffer(m_Window->GetWinData());

	cube = new graphics::RenderCube("shader/cubeVertex.vert","shader/cubeFragment.frag");

}

Application::~Application()
{
	delete imgui;
	delete renderLayer;
	delete layerList;
	delete framebuffer;
}

void Application::Run()
{
	auto& WinData = m_Window->GetWinData();

	

	while (!m_Window->Closed())
	{	
		//bind framebuffer
		m_Window->Clear();
		framebuffer->BindFrameBuffer();
		framebuffer->UpdateFramebufferTex(WinData);
		
		m_Window->Clear();
		m_Window->ClearColor();
		cube->Draw();
		
		//default framebuffer
		framebuffer->UnbindFrameBuffer();
		
		imgui->Begin();
		renderLayer->TestDraw(WinData,framebuffer->GetRendered());
		imgui->OnImguiLayer();


		imgui->End();
		
		//std::cout << m_Window->GetCursorPosX() << "   " << m_Window->GetCursorPosY() << std::endl;


		framebuffer->DelFramebufferTex();

		m_Window->OnUpdate();
	}

	imgui->OnDetach();
}














