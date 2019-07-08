#include "Application.h"

Application::Application()
{
	m_Window = std::unique_ptr<graphics::Window>(graphics::Window::Create());

	layerstack = new graphics::LayerStack();

	imgui = new graphics::ImguiLayer(m_Window->GetWinPros());
	imgui->OnAttach();


	layerstack->PushLayer(imgui);

	render = new graphics::Render();
}

Application::~Application()
{
}

void Application::Run()
{
	render->use();

	while (!m_Window->Closed())
	{
		//clear buffers
		m_Window->Clear();

		
		imgui->Begin();

		render->Draw();
		layerstack->ShowLayer();


		imgui->End();


		//swap buffers
		m_Window->OnUpdate();
	}


	imgui->OnDetach();
}
