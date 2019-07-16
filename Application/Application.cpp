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

	framebuffer = new graphics::FrameBuffer(m_Window->GetWinWidth(), m_Window->GetWinHeight());
	
}

Application::~Application()
{
}

void Application::Run()
{


	while (!m_Window->Closed())
	{	
		framebuffer->BindFrameBuffer();
		imgui->Begin();

		renderLayer->OnImguiLayer();

		imgui->End();
		//glClear(GL_COLOR_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		//glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT);
		//glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

		//clear buffers
		framebuffer->UnbindFrameBuffer();
		m_Window->Clear();
		//
		//imgui->Begin();

		//layerList->RenderLayers();
		//renderLayer->OnImguiLayer();
		renderLayer->OnAttach();
		//imgui->End();
		//
		//swap buffers
		m_Window->OnUpdate();
	}


	imgui->OnDetach();
}
