#include "graphics/Window.h"
#include <direct.h>
namespace renderx {
	namespace graphics {
		
		Window* Window::m_Instance = nullptr;

		Window* Window::Create()
		{
			if(m_Instance==nullptr)
				m_Instance = new Window();
			return m_Instance;
		}

		Window::~Window()
		{
			glfwDestroyWindow(m_WinPros.glWindowPtr);
		}


		Window::Window()
		{
			if (!init())
				RDX_INIT_ERROR(init(), "Init failed");
			else 
				RDX_INIT_SUCCESS(init(), "Init successfully");

		}

		bool Window::init()
		{
			if (glfwInit() != GLFW_TRUE)
			{
				RDX_INIT_ERROR(glfwInit(), "Init failed");
				return false;
			}
			else
				RDX_INIT_SUCCESS(glfwInit(), "Init successfully");
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			m_WinPros.glWindowPtr = glfwCreateWindow(
				m_WinPros.win_Width,
				m_WinPros.win_Height,
				m_WinPros.win_Title.c_str(),
				nullptr,
				nullptr
			);

			glfwMakeContextCurrent(m_WinPros.glWindowPtr);


			if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
			{
				std::cout << "Failed to initialize the glad" << std::endl;
				glfwTerminate();
				return false;
			}

			return true;

		}


		void Window::Clear()const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		}


		bool Window::Closed()const
		{
			return glfwWindowShouldClose(m_WinPros.glWindowPtr) == 1;
		}

		void Window::OnUpdate()const
		{
			glfwSwapBuffers(m_WinPros.glWindowPtr);
			glfwPollEvents();
		}

	}
}