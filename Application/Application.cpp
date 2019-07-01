#include "Application.h"

Application::Application()
{
	m_Window = std::unique_ptr<graphics::Window>(graphics::Window::Create());


	//gui = new graphics::Imgui();
	layerstack = new graphics::LayerStack();

	imgui = new graphics::ImguiLayer(m_Window->GetWinPtr());

	layerstack->PushLayer(imgui);
}

Application::~Application()
{
}

void Application::Run()
{
	//gui->set(m_Window->GetWinPtr());


	while (!m_Window->Closed())
	{
		//clear buffers
		m_Window->Clear();

		/*gui->begin();
		gui->show();
		gui->end(m_Window->GetWinPtr());
		*/
		
		imgui->Begin();
		layerstack->ShowLayer();
		imgui->End(m_Window->GetWinPtr());


		//swap buffers
		m_Window->OnUpdate();
	}
}
