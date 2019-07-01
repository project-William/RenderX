#pragma once
#include <RenderX.h>


using namespace renderx;

class Application
{
private:
	std::unique_ptr<graphics::Window> m_Window;

	graphics::Imgui* gui;
	

private:



public:
	Application();
	~Application();

	void Run();

};