#include "Application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define EVENT_LOG(x,message) { std::cout<<"EVENT:"#x<<" "<<message<<std::endl; }

Application::Application()
{
	m_Window = std::unique_ptr<graphics::Window>(graphics::Window::Create());
	m_Window->SetEventCallback(BIND_EVENT(Application::OnEvent));
	
	renderLayer = new graphics::RenderLayer(m_Window->GetWinData());
	
	imgui = new graphics::ImguiLayer(m_Window->GetWinPtr(), m_Window->GetWinData());

	imgui->OnAttach();

	layerList = new graphics::LayerList();
	layerList->PushBackLayer(imgui);
	layerList->PushBackLayer(renderLayer);	
	framebuffer = new graphics::FrameBuffer(m_Window->GetWinData());

	cube = new graphics::RenderCube("shader/cubeVertex.vert","shader/cubeFragment.frag");
	sphere = new graphics::RenderSphere("shader/sphereVertex.vert", "shader/sphereFragment.frag");

	

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

	//input = new utils::Input(WinData);

	while (m_Running)
	{	
		/*****************************bind framebuffer******************************/
		m_Window->Clear();
		framebuffer->BindFrameBuffer();
		framebuffer->UpdateFramebufferData(WinData,m_WindowResized_flag);
		m_Window->Clear();
		m_Window->ClearColor();

		//begin scene
		sphere->Draw(WinData);
		//cube->Draw(WinData);
		//end scene
		/***************************default framebuffer*******************************/
		framebuffer->UnbindFrameBuffer();
		imgui->Begin();
		
		renderLayer->TestDraw(WinData,framebuffer->GetRendered());
		//imgui setting window
		imgui->SettingWindowBegin();
		
		//cube->Color(WinData);
		sphere->Color(WinData);
		
		imgui->SettingWindowEnd();
	
		imgui->End();		
		
		m_Window->OnUpdate();
		m_WindowResized_flag = false;
	}

	imgui->OnDetach();
}



void Application::OnEvent(events::Event& e)
{
	bool handled = false;
	events::EventDispatcher dispatcher(e);

	if (e.IsInCategory(events::RX_EVENT_CATEGORY_WINDOW))
	{
		if (!handled)
		{
			handled = dispatcher.Dispatch<events::WindowResizedEvent>(BIND_EVENT(Application::OnWindowResizedEvent));
		}

		if (!handled)
		{
			handled = dispatcher.Dispatch<events::WindowClosedEvent>(BIND_EVENT(Application::OnWindowClosedEvent));
		}

		if (!handled)
		{
			handled = dispatcher.Dispatch<events::WindowMovedEvent>(BIND_EVENT(Application::OnWindowMovedEvent));
		}
	}

	else if(e.IsInCategory(events::RX_EVENT_CATEGORY_KEYBOARD))
	{
		if (!handled)
		{
			handled = dispatcher.Dispatch<events::KeyPressedEvent>(BIND_EVENT(Application::OnKeyPressedEvent));
		}

		if (!handled)
		{
			handled = dispatcher.Dispatch<events::KeyReleasedEvent>(BIND_EVENT(Application::OnKeyReleasedEvent));
		}

	}

	else if (e.IsInCategory(events::RX_EVENT_CATEGORY_MOUSE))
	{
		if (!handled)
		{
			handled = dispatcher.Dispatch<events::MouseMovedEvent>(BIND_EVENT(Application::OnMouseMovedEvent));
		}
		

		if (!handled)
		{
			handled = dispatcher.Dispatch<events::MousePressedEvent>(BIND_EVENT(Application::OnMouseButtonPressed));
		}

		if (!handled)
		{
			handled = dispatcher.Dispatch<events::MouseRelasedEvent>(BIND_EVENT(Application::OnMouseButtonReleased));
		}

		if (!handled)
		{
			handled = dispatcher.Dispatch<events::MouseScrollEvent>(BIND_EVENT(Application::OnMouseScrollEvent));
		}

	}
}

bool Application::OnWindowResizedEvent(events::WindowResizedEvent& e)
{
	m_Window->OnWindowResized();
	EVENT_LOG(events::WindowResizedEvent, "Window resized");
	m_WindowResized_flag = true;
	return true;
}

bool Application::OnWindowClosedEvent(events::WindowClosedEvent& e)
{
	m_Running = false;
	EVENT_LOG(events::WindowClosedEvent, "Window closed");
	return true;
}

bool Application::OnWindowMovedEvent(events::WindowMovedEvent& e)
{
	EVENT_LOG(events::WindowMovedEvent, "Window moved");
	return true;
}

bool Application::OnMouseButtonPressed(events::MousePressedEvent& e)
{
	return false;
}

bool Application::OnMouseButtonReleased(events::MouseRelasedEvent& e)
{
	return false;
}

bool Application::OnMouseMovedEvent(events::MouseMovedEvent& e)
{
	return false;
}

bool Application::OnMouseScrollEvent(events::MouseScrollEvent& e)
{
	return false;
}

bool Application::OnKeyPressedEvent(events::KeyPressedEvent& e)
{
	return false;
}

bool Application::OnKeyReleasedEvent(events::KeyReleasedEvent& e)
{
	return false;
}










