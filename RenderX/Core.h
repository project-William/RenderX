#pragma once
#include <iostream>
#include <string>
#include <memory>


#ifdef RENDERX
	#define REN_API __declspec(dllimport)
#else
	#define REN_API __declspec(dllexport)
#endif // RENDERX
