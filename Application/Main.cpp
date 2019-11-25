#include "Application.h"

#ifdef RENDERX_DLL

int main()
{

	std::unique_ptr<Application> app(new Application());
	app->Run();

	//std::cout << static_cast<unsigned int>(-1) << std::endl;

	return 0;
}

#endif // RENDERX_DLL
