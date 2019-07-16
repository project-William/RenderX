#include "Application.h"

Application::Application()
{
	m_Window = std::unique_ptr<graphics::Window>(graphics::Window::Create());

	renderLayer = new graphics::RenderLayer();
	//
	imgui = new graphics::ImguiLayer(m_Window->GetWinPros());

	imgui->OnAttach();

	layerList = new graphics::LayerList();
	layerList->PushBackLayer(imgui);
	layerList->PushBackLayer(renderLayer);
	
	framebuffer = new graphics::FrameBuffer();
}

Application::~Application()
{
}

void Application::Run()
{
	
	while (!m_Window->Closed())
	{
		//framebuffer->BindFrameBuffer();
		//glClear(GL_COLOR_BUFFER_BIT);
		//glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

		//clear buffers
		m_Window->Clear();

		
		imgui->Begin();

		layerList->RenderLayers();

		imgui->End();
		
		//swap buffers
		m_Window->OnUpdate();
	}


	imgui->OnDetach();
}
