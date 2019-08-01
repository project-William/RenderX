#include "Application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define EVENT_LOG(x,message) { std::cout<<"EVENT:"#x<<" "<<message<<std::endl; }

Application::Application()
{

	m_Window = std::unique_ptr<graphics::Window>(graphics::Window::Create());
	m_Keyboard = utils::Keyboard::Create();
	m_Mouse = utils::Mouse::Create();

	m_Window->SetEventCallback(BIND_EVENT(Application::OnEvent));

	renderLayer = new graphics::RenderLayer(m_Window->GetWinData());
	
	imgui = new ui::ImguiLayer(m_Window->GetWinData());

	imgui->OnAttach();
	
	layerList = new graphics::LayerList();
	layerList->PushBackLayer(imgui);
	layerList->PushBackLayer(renderLayer);	
	framebuffer = new graphics::FrameBuffer(m_Window->GetWinData());

	cube = new graphics::RenderCube("shader/cubeVertex.vert","shader/cubeFragment.frag");
	sphere = new graphics::RenderSphere("shader/sphereVertex.vert", "shader/sphereFragment.frag");
	skybox = new entity::RenderSkybox("shader/cubemapVertex.vert", "shader/cubemapFragment.frag");

	imguiLog = new ui::ImguiLog();
	imguisetwindow=new ui::ImguiSetWindow();
	imguiSceneWindow = new ui::ImguiSceneWindow();

	camera = new entity::FPSCamera(glm::vec3(0.0f, 0.0f, 3.0f));

	basicLight = new graphics::BasicLight();

}

Application::~Application()
{
	delete imgui;
	delete renderLayer;
	delete layerList;
	delete framebuffer;
	delete skybox;
}

void Application::Run()
{
	auto& WinData = m_Window->GetWinData();


	while (m_Running)
	{	
		/*****************************bind framebuffer******************************/
		m_Window->Clear();
		framebuffer->BindFrameBuffer();
		framebuffer->UpdateFramebufferData(WinData,m_WindowResized_flag);
		m_Window->Clear();
		m_Window->ClearColor();
		//begin scene
		graphics::RenderScene::SceneBegin();

		skybox->Draw(WinData,camera);
		sphere->Draw(WinData);

		//cube->Draw(WinData);
		
		graphics::RenderScene::SceneEnd();
		//end scene
		/***************************default framebuffer*******************************/
		framebuffer->UnbindFrameBuffer();
		imgui->Begin();
		
		//imgui setting window
		imguisetwindow->BeginSetWindow();
		imguisetwindow->GraphicsSettingWindow();
		sphere->SphereSetting(WinData, camera);
		sphere->PhongModel(basicLight, camera);
		sphere->Color(WinData);
		renderLayer->RenderSettings();
		imguisetwindow->EndSetWindow();
		//movement
		//sphere->GetTrans().view = camera->GetViewMatrix();
		
		//imgui draw window
		imguiSceneWindow->BeginSceneWindow();
		imguiSceneWindow->SceneWindow(WinData, framebuffer->GetRendered());
		imguiSceneWindow->EndSceneWindow();
		//keyboard movement
		
		//imgui log window
		imguiLog->BeginLog();
		imguiLog->EndLog();
		
		imgui->End();		
		m_WindowResized_flag = false;
		//framebuffer->UnbindFrameBuffer();
		//skybox->Draw(WinData,camera);
		//
		//sphere->Draw(WinData);
		//sphere->SphereSetting(WinData,camera);

		m_Window->OnUpdate();
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
			EVENT_LOG(events::WindowResizedEvent, "Window resized!");
		}

		if (!handled)
		{
			handled = dispatcher.Dispatch<events::WindowClosedEvent>(BIND_EVENT(Application::OnWindowClosedEvent));
			EVENT_LOG(events::WindowClosedEvent, "Window colsed!");
		}

		if (!handled)
		{
			handled = dispatcher.Dispatch<events::WindowMovedEvent>(BIND_EVENT(Application::OnWindowMovedEvent));
			EVENT_LOG(events::WindowMovedEvent, "Window moved!");
		}
	}

	else if(e.IsInCategory(events::RX_EVENT_CATEGORY_KEYBOARD))
	{
		if (!handled)
		{
			handled = dispatcher.Dispatch<events::KeyPressedEvent>(BIND_EVENT(Application::OnKeyPressedEvent));
			EVENT_LOG(events::KeyPressedEvent, "KeyPressed!");
		}

		if (!handled)
		{
			handled = dispatcher.Dispatch<events::KeyReleasedEvent>(BIND_EVENT(Application::OnKeyReleasedEvent));
			EVENT_LOG(events::KeyPressedEvent, "KeyReleased!");
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
	utils::Mouse::GetMouseInstance()->OnEvent(e);
	EVENT_LOG(events::MousePressedEvent, "Mouse Pressed!");
	return true;
}

bool Application::OnMouseButtonReleased(events::MouseRelasedEvent& e)
{
	utils::Mouse::GetMouseInstance()->OnEvent(e);
	EVENT_LOG(events::MouseRelasedEvent, "Mouse Released!");
	return true;
}

bool Application::OnMouseMovedEvent(events::MouseMovedEvent& e)
{
	utils::Mouse::GetMouseInstance()->OnEvent(e);
	EVENT_LOG(events::MouseMovedEvent, "Mouse Moved!");
	return true;
}

bool Application::OnMouseScrollEvent(events::MouseScrollEvent& e)
{
	utils::Mouse::GetMouseInstance()->OnEvent(e);
	EVENT_LOG(events::MouseScrollEvent, "Mouse Scroll moved!");
	return true;
}

bool Application::OnKeyPressedEvent(events::KeyPressedEvent& e)
{
	utils::Keyboard::GetKeyboardInstance()->OnEvent(e);
	return true;
}

bool Application::OnKeyReleasedEvent(events::KeyReleasedEvent& e)
{
	utils::Keyboard::GetKeyboardInstance()->OnEvent(e);
	return true;
}










