#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <deque>
#include <list>
#include <functional>
#include <Windows.h>
#include <future>
#include <string>
#include <memory>
#include <optional>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <thread>
#include <chrono>

//glfw + glad
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//opengl 3D math library
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

//imgui
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

//model
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>

#pragma warning(disable : 4251)
#pragma warning(disable : 26812)
#pragma warning(disable : 26495)
#pragma warning(disable : 26451)

#define TWO_SQUARE(x) (1<<x)

#ifdef RENDERX_DLL
#define REN_API __declspec(dllimport)
#else
#define REN_API __declspec(dllexport)
#endif // RENDERX

#define BIND_EVENT(x) std::bind(&x, this, std::placeholders::_1)

#define ASPECT_IN_RANGE(x) isnan(x) == true ? 1.0f : x


