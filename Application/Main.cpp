#include "Application.h"
using namespace renderx;

#ifdef RENDERX_DLL

int main(int argc,char** argv)
{

	Application* app = new Application();
	app->Run();
	delete app;
	
	
	return 0;
}

#endif //RENDERX