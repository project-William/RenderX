#include "graphics/Window.h"

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
			glfwDestroyWindow(m_WinData.glWindowPtr);
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
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			m_WinData.glWindowPtr = glfwCreateWindow(
				m_WinData.win_Width,
				m_WinData.win_Height,
				m_WinData.win_Title.c_str(),
				nullptr,
				nullptr
			);

			glfwMakeContextCurrent(m_WinData.glWindowPtr);
			glfwSetWindowUserPointer(m_WinData.glWindowPtr,&m_WinData);

			glfwSetWindowSizeCallback(m_WinData.glWindowPtr, [](GLFWwindow* window, int width, int height)
			{
				WinData& data = *(WinData*)glfwGetWindowUserPointer(window);
				data.win_Width = width;
				data.win_Height = height;
				events::WindowResizedEvent event(width, height);
				
			});
			
			glfwSetCursorPosCallback(m_WinData.glWindowPtr, [](GLFWwindow* window, double xPos, double yPos)
			{
				WinData& data = *(WinData*)glfwGetWindowUserPointer(window);
				data.xpos = xPos;
				data.ypos = yPos;
				events::MouseMovedEvent event((float)xPos, (float)yPos);
			});





			if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
			{
				RDX_INIT_ERROR(gladLoadGLLoader, "Failed to initialize GLAD!");
				glfwTerminate();
				return false;
			}
			else
				RDX_INIT_SUCCESS(gladLoadGLLoader, "GLAD initialized successfully!");
		
			return true;
		}


		void Window::Clear()const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
		
		void Window::ClearColor()const
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		}


		bool Window::Closed()const
		{
			return glfwWindowShouldClose(m_WinData.glWindowPtr) == 1;
		}

		void Window::OnUpdate()const
		{
			glfwSwapBuffers(m_WinData.glWindowPtr);
			glfwPollEvents();
		}

	}
}