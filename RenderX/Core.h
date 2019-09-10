#pragma once
#include <iostream>
#include <memory>
#include <math.h>	
#include <sstream>
#include <fstream>
#include <utility>
#include <vector>
#include <filesystem>
#include <array>	
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <direct.h>
#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <optional>

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "include/utils/Log.h"

#ifdef RENDERX_DLL
	#define REN_API __declspec(dllimport)
#else
	#define REN_API __declspec(dllexport)
#endif // RENDERX

#define SINGLE_CHOICE_IN_TWO(a,b) if(a) { b=false; }

#define SINGLE_CHOICE_IN_THREE(a,b,c) if(a) { b=c=false; }

#define SINGLE_CHOICE_IN_FOUR(a,b,c,d) if(a) { b=c=d=false; }

#define SINGLE_CHOICE_IN_FIVE(a,b,c,d,e) if(a) { b=c=d=e=false; }

#define VALUE(x) (1<<x)

#define MAX_FILE_DIALOG_NAME_BUFFER 1024

#define BIND_EVENT(x) std::bind(&x, this, std::placeholders::_1)

#define ASPECT_IN_RANGE(x) isnan(x) == true ? 1.0f : x

//#define RDX_INIT_ERROR(x,...) if(!(x)) renderx::utils::Log::LogInit(#x,__FILE__,__LINE__,##__VA_ARGS__)
//
//#define RDX_INIT_SUCCESS(x,...) renderx::utils::Log::LogInit(#x,__FILE__,__LINE__,##__VA_ARGS__)
//
//#define RDX_EVENT_LOG(x,log) renderx::utils::Log::LogEvent(#x, log)	




