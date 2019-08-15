#pragma once
#include <RenderX.h>


using namespace renderx;

class Application
{
private:
	std::unique_ptr<graphics::Window> m_Window;
	
	entity::FPSCamera* camera;

	ui::ImguiLayer* imgui = nullptr;

	graphics::RenderLayer* renderLayer = nullptr;

	graphics::LayerList* layerList = nullptr;

	graphics::FrameBuffer* framebuffer;

	graphics::RenderCube* cube;

	graphics::RenderSphere* sphere;

	entity::RenderSkybox* skybox_1;
	entity::RenderSkybox* skybox_2;
	entity::RenderSkybox* skybox_3;
	entity::RenderSkybox* skybox_4;

	entity::Flatboard* flatboard;

	ui::ImguiLog* imguiLog;

	ui::ImguiSetWindow* imguisetwindow;

	std::shared_ptr<utils::Mouse> m_Mouse;
	std::shared_ptr<utils::Keyboard> m_Keyboard;
	
	ui::ImguiSceneWindow* imguiSceneWindow;

	graphics::RenderLight* basicLight;
	graphics::RenderLight* lights[4];

	bool m_Running = true;
	bool m_WindowResized_flag = false;


	

private:
	entity::CubemapFaces cubemapfaces;

	void OnEvent(events::Event& e);
	
	bool OnWindowResizedEvent(events::WindowResizedEvent& e);
	bool OnWindowClosedEvent(events::WindowClosedEvent& e);
	bool OnWindowMovedEvent(events::WindowMovedEvent& e);
	
	bool OnMouseButtonPressed(events::MousePressedEvent& e);
	bool OnMouseButtonReleased(events::MouseRelasedEvent& e);
	bool OnMouseMovedEvent(events::MouseMovedEvent& e);
	bool OnMouseScrollEvent(events::MouseScrollEvent& e);
	
	bool OnKeyPressedEvent(events::KeyPressedEvent& e);
	bool OnKeyReleasedEvent(events::KeyReleasedEvent& e);
	

public:
	Application();
	~Application();

	void Run();

};