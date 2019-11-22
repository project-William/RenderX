#include "Application.h"

#ifdef RENDERX_DLL

int main()
{

	std::unique_ptr<Application> app(new Application());
	app->Run();


	std::list<std::string> list;
	list.push_back("cherno");
	list.push_back("cherno1");
	list.push_back("cherno3");
	list.push_back("cherno4");
	
	for (auto it = list.rbegin(); it != list.rend(); it++)
	{
		if (it->find("cherno") != std::string::npos)
		{
			list.erase(--it.base());
			break;
		}
	}

	for (auto it : list)
	{
		std::cout << it << std::endl;
	}

	return 0;
}

#endif // RENDERX_DLL
