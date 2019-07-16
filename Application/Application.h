#pragma once
#include <RenderX.h>


using namespace renderx;

class Application
{
private:
	std::unique_ptr<graphics::Window> m_Window;

	graphics::ImguiLayer* imgui = nullptr;

	graphics::RenderLayer* renderLayer = nullptr;

	graphics::LayerList* layerList = nullptr;

	graphics::FrameBuffer* framebuffer;
private:



public:
	Application();
	~Application();

	void Run();

};