#include <iostream>
#include "RenderX.h"

using namespace renderx;

int main(int argc,char** argv)
{
	graphics::Window window = graphics::Window::Create();

	while (!window.Closed())
	{
		window.Clear();
		window.OnUpdate();
	}
	
	return 0;
}