#include "Window.h"
#include "event/MouseEvent.h"
#include "event/WindowEvent.h"
#include "event/KeyboardEvent.h"

namespace renderx {

	std::shared_ptr<Window> Window::m_Instance = nullptr;

	std::shared_ptr<Window> Window::Create()
	{
		if (m_Instance == nullptr)
		{
			m_Instance = std::shared_ptr<Window>(new Window());
			return m_Instance;
		}
		return m_Instance;
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_WinData.glWindowPtr);
	}

	Window::Window()
	{
		if (!init())
			std::cout << "filed" << std::endl;
		else
			std::cout << "success" << std::endl;
	}

	bool Window::init()
	{
		if (glfwInit() != GLFW_TRUE)
		{
			std::cout << "failed" << std::endl;
			return false;
		}
		else
		{
			std::cout << "success" << std::endl;
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_SAMPLES, 4);

		m_WinData.glWindowPtr = glfwCreateWindow(
			m_WinData.m_Width,
			m_WinData.m_Height,
			m_WinData.m_Title,
			nullptr,
			nullptr
		);

		glfwMakeContextCurrent(m_WinData.glWindowPtr);
		glfwSetWindowUserPointer(m_WinData.glWindowPtr, &m_WinData);

		glfwSetWindowSizeCallback(m_WinData.glWindowPtr, [](GLFWwindow* window, int width, int height)
		{
			WinData& data = *static_cast<WinData*>(glfwGetWindowUserPointer(window));
			data.m_Width = width;
			data.m_Height = height;
			events::WindowResizedEvent event(width, height);
			data.OnEvent(event);
		});


		glfwSetWindowCloseCallback(m_WinData.glWindowPtr, [](GLFWwindow* window)
		{
			WinData& data = *static_cast<WinData*>(glfwGetWindowUserPointer(window));
			events::WindowClosedEvent event;
			data.OnEvent(event);
		});

		glfwSetCursorPosCallback(m_WinData.glWindowPtr, [](GLFWwindow* window, double xPos, double yPos)
		{
			WinData& data = *static_cast<WinData*>(glfwGetWindowUserPointer(window));
			data.mouse_xpos = static_cast<float>(xPos);
			data.mouse_ypos = static_cast<float>(yPos);
			events::MouseMovedEvent event((float)xPos, (float)yPos);
			data.OnEvent(event);
		});


		glfwSetKeyCallback(m_WinData.glWindowPtr, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WinData& data = *static_cast<WinData*>(glfwGetWindowUserPointer(window));
			static int repeatCount = 0;

			switch (action)
			{
			case GLFW_PRESS:
			{
				repeatCount = 1;
				events::KeyPressedEvent event(key, repeatCount);
				data.OnEvent(event);
				break;
			}

			case GLFW_RELEASE:
			{
				repeatCount = 0;
				events::KeyReleasedEvent event(key);
				data.OnEvent(event);
				break;
			}

			case GLFW_REPEAT:
			{
				repeatCount++;
				events::KeyPressedEvent event(key, repeatCount);
				data.OnEvent(event);
				break;
			}
			}
		});


		glfwSetMouseButtonCallback(m_WinData.glWindowPtr, [](GLFWwindow* window, int button, int action, int mods)
		{
			auto& data = *static_cast<WinData*>(glfwGetWindowUserPointer(window));
			switch (action)
			{
			case GLFW_PRESS:
			{
				events::MousePressedEvent event(button);
				data.OnEvent(event);
				break;
			}

			case GLFW_RELEASE:
			{
				events::MouseRelasedEvent event(button);
				data.OnEvent(event);
				break;
			}
			}
		});

		glfwSetScrollCallback(m_WinData.glWindowPtr, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			auto& data = *static_cast<WinData*>(glfwGetWindowUserPointer(window));
			events::MouseScrollEvent event((float)xOffset, (float)yOffset);
			data.OnEvent(event);
		});

		if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
		{
			std::cout << "failed" << std::endl;
			glfwTerminate();
			return false;
		}
		else
			std::cout << "success" << std::endl;
		
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

	void Window::ConfigViewport(int32_t width, int32_t height)
	{
		glViewport(0, 0, width, height);
	}

	void Window::ConfigFrameSize()
	{
		int32_t width, height;
		glfwGetFramebufferSize(m_WinData.glWindowPtr, &width, &height);
		ConfigViewport(width, height);
	}

	void Window::OnWindowResized()
	{
		glViewport(0, 0, m_WinData.m_Width, m_WinData.m_Height);
	}

	void Window::OnUpdate()const
	{
		glfwSwapBuffers(m_WinData.glWindowPtr);
		glfwPollEvents();
	}

}