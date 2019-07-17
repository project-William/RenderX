#include "Application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>


Application::Application()
{
	m_Window = std::unique_ptr<graphics::Window>(graphics::Window::Create());

	auto& winPros = m_Window->GetWinPros();

	renderLayer = new graphics::RenderLayer(m_Window->GetWinPros());
	//
	imgui = new graphics::ImguiLayer(m_Window->GetWinPros());

	imgui->OnAttach();

	layerList = new graphics::LayerList();
	layerList->PushBackLayer(imgui);
	layerList->PushBackLayer(renderLayer);

	
}

Application::~Application()
{
}

void Application::Run()
{


	while (!m_Window->Closed())
	{	
		//renderLayer->GetFrameBuffer()->BindFrameBuffer();
		//imgui->Begin();
		//renderLayer->TestDraw();
		//
		//imgui->End();
		//
		////clear buffers
		//renderLayer->GetFrameBuffer()->UnbindFrameBuffer();
		//m_Window->Clear();
		//
		//imgui->Begin();

		//layerList->RenderLayers();
		//renderLayer->OnImguiLayer();
		//renderLayer->TestDraw();
		
		//imgui->End();
		//
		//swap buffers
		m_Window->Clear();
		
		renderLayer->OnAttach();
		std::cout << m_Window->GetWinWidth() << " " << m_Window->GetWinHeight() << std::endl;

		m_Window->OnUpdate();
	}


	imgui->OnDetach();
}
