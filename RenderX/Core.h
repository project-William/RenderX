#pragma once
#include <memory>
#include <sstream>
#include <fstream>
#include <utility>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <direct.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

#include "include/utils/Log.h"

#ifdef RENDERX_DLL
	#define REN_API __declspec(dllimport)
#else
	#define REN_API __declspec(dllexport)
#endif // RENDERX

#define VALUE(x) (1<<x)

#define RDX_INIT_ERROR(x,...) if(!(x)) renderx::utils::Log::LogInit(#x,__FILE__,__LINE__,##__VA_ARGS__)

#define RDX_INIT_SUCCESS(x,...) renderx::utils::Log::LogInit(#x,__FILE__,__LINE__,##__VA_ARGS__)





