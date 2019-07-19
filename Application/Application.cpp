#include "Application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>


Application::Application()
{
	m_Window = std::unique_ptr<graphics::Window>(graphics::Window::Create());

	auto& WinData = m_Window->GetWinData();

	renderLayer = new graphics::RenderLayer(m_Window->GetWinData());
	//
	imgui = new graphics::ImguiLayer(m_Window->GetWinPtr(), m_Window->GetWinData());

	imgui->OnAttach();

	layerList = new graphics::LayerList();
	layerList->PushBackLayer(imgui);
	layerList->PushBackLayer(renderLayer);	

}

Application::~Application()
{
	delete imgui;
	delete renderLayer;
	delete layerList;
}

void Application::Run()
{


	while (!m_Window->Closed())
	{	
		m_Window->Clear();
		m_Window->ClearColor();
		renderLayer->GetFrameBuffer()->BindFrameBuffer();
		//imgui->Begin();
		m_Window->Clear();
		m_Window->ClearColor();
		renderLayer->OnAttach();
		//renderLayer->TestDraw();
		//imgui->OnImguiLayer();
		//imgui->End();
		
		//clear buffers
		//m_Window->OnUpdate();
		renderLayer->GetFrameBuffer()->UnbindFrameBuffer();
		imgui->Begin();
		renderLayer->TestDraw(m_Window->GetWinWidth(), m_Window->GetWinHeight());
		imgui->OnImguiLayer();


		imgui->End();
		//

		//layerList->RenderLayers();
		//renderLayer->OnImguiLayer();
		//renderLayer->TestDraw();
		//imgui->OnImguiLayer();
		//imgui->End();
		//
		//swap buffers
		//m_Window->Clear();
		
		//renderLayer->OnAttach();
		//std::cout << m_Window->GetWinWidth() << " " << m_Window->GetWinHeight() << std::endl;

		m_Window->OnUpdate();
	}


	imgui->OnDetach();
}
