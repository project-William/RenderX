#include "Application.h"

using namespace renderx;

#ifdef RENDERX_DLL

int main(int argc,char** argv)
{
	
	std::unique_ptr<Application> app(new Application());
	app->Run();
	return 0;
}

#endif //RENDERX_DLL