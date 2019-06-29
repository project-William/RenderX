#include "Application.h"
using namespace renderx;

//#define RENDERX in preprocesser
#ifdef RENDERX_DLL

int main(int argc,char** argv)
{
	Application* app = new Application();
	app->Run();
	delete app;
	
	return 0;
}

#endif //RENDERX