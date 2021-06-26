#include "pch.h"
#include "Window.h"
#include "glad/src/glad.c"

#include "Event/MouseEvent.h"
#include "Event/KeyEvent.h"
#include "Event/WindowEvent.h"


namespace renderx::base
{
	std::shared_ptr<Window> Window::s_Instance;

	std::shared_ptr<Window>& Window::Get()
	{
		if (!s_Instance)
		{
			s_Instance = std::shared_ptr<Window>(new Window());
		}
		return s_Instance;
	}

	Window::Window()
	{
		if (!Init())
		{
			std::cout << "failed to init window" << std::endl;
		}
	}

	void Window::OnUpdate()
	{
		glfwSwapBuffers(m_Data.m_WinPtr);
		glfwPollEvents();
	}

	void Window::ClearColor(float r,float g,float b,float a)
	{
		glClearColor(r, g, b, a);
	}

	void Window::ClearBuffer()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::ConfigViewport(int width, int height) 
	{
		glViewport(0, 0, width, height);
	}

	bool Window::Init()
	{
		if (glfwInit() != true)
			return false;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_SAMPLES, 4);


		m_Data.m_WinPtr = glfwCreateWindow(m_Data.m_Width, m_Data.m_Height, m_Data.m_Title.c_str(), nullptr, nullptr);
		if (!m_Data.m_WinPtr)
		{
			return false;
		}



		glfwMakeContextCurrent(m_Data.m_WinPtr);
		bool status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (!status)
		{
			std::cout << "failed to initialize the glad" << std::endl;
			return false;
		}
		glfwSetWindowUserPointer(m_Data.m_WinPtr, &m_Data);

		glfwSetWindowSizeCallback(m_Data.m_WinPtr, [](GLFWwindow* window, int width, int height)
		{
			auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			data.m_Width = width;
			data.m_Height = height;
			data.m_IsWindowResized = true;
			WindowResizedEvent event(width, height);
			data.OnEvent(event);
		});


		glfwSetWindowCloseCallback(m_Data.m_WinPtr, [](GLFWwindow* window)
		{
			auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			WindowClosedEvent event;
			data.OnEvent(event);
		});

		glfwSetCursorPosCallback(m_Data.m_WinPtr, [](GLFWwindow* window, double xPos, double yPos)
		{
			auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			data.mouse_x = static_cast<float>(xPos);
			data.mouse_y = static_cast<float>(yPos);
			MouseMovedEvent event((float)xPos, (float)yPos);
			data.OnEvent(event);
		});


		glfwSetKeyCallback(m_Data.m_WinPtr, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			static int repeatCount = 0;

			switch (action)
			{
			case GLFW_PRESS:
			{
				repeatCount = 1;
				KeyPressedEvent event(key, repeatCount);
				data.OnEvent(event);
				break;
			}

			case GLFW_RELEASE:
			{
				repeatCount = 0;
				KeyReleasedEvent event(key);
				data.OnEvent(event);
				break;
			}

			case GLFW_REPEAT:
			{
				repeatCount++;
				KeyPressedEvent event(key, repeatCount);
				data.OnEvent(event);
				break;
			}
			}
		});


		glfwSetMouseButtonCallback(m_Data.m_WinPtr, [](GLFWwindow* window, int button, int action, int mods)
		{
			auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			switch (action)
			{
			case GLFW_PRESS:
			{
				MousePressedEvent event(button);
				data.OnEvent(event);
				break;
			}

			case GLFW_RELEASE:
			{
				MouseRelasedEvent event(button);
				data.OnEvent(event);
				break;
			}
			}
		});

		glfwSetScrollCallback(m_Data.m_WinPtr, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			MouseScrollEvent event((float)xOffset, (float)yOffset);
			data.OnEvent(event);
		});

		glEnable(GL_DEPTH_TEST);
		
		glEnable(GL_MULTISAMPLE);
		return true;
	}

	bool Window::Close()
	{
		return glfwWindowShouldClose(m_Data.m_WinPtr) == 1;
	}

	
}