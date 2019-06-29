#include "Application.h"

Application::Application()
{
	m_Window = std::unique_ptr<graphics::Window>(graphics::Window::Create());


}

Application::~Application()
{
}

void Application::Run()
{
	while (!m_Window->Closed())
	{
		//clear buffers
		m_Window->Clear();




		//swap buffers
		m_Window->OnUpdate();
	}
}
