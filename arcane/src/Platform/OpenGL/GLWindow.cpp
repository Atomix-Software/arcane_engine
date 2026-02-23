#include "aepch.h"
#include "Platform/OpenGL/GLWindow.h"

#include "Arcane/Core/Log.h"

#include "Arcane/Events/ApplicationEvent.h"
#include "Arcane/Events/KeyEvent.h"
#include "Arcane/Events/MouseEvent.h"

#include <glad/glad.h>

namespace Arcane
{

	static bool s_GLFWInitialized = false;
	static void GLFWErrorCallback(int error, const char* description)
	{
		AE_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window* Window::Create(const WindowProps& properties)
	{
		return new GLWindow(properties);
	}

	GLWindow::GLWindow(const WindowProps& properties)
	{
		Init(properties);
	}

	GLWindow::~GLWindow()
	{
		Shutdown();
	}

	void GLWindow::Init(const WindowProps& properties)
	{
		m_Data.Title = properties.Title;
		m_Data.Width = properties.Width;
		m_Data.Height = properties.Height;

		AE_CORE_INFO("Creating Window {0} ({1}, {2})", properties.Title, properties.Width, properties.Height);

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			AE_CORE_ASSERT(success, "Could not initialize GLFW!");

			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int) m_Data.Width, (int) m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		AE_CORE_ASSERT(status, "Failed to initialize OpenGL!");
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Setup the callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* handle, int width, int height) 
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(handle);
				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* handle)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(handle);
				WindowCloseEvent event;
				data.EventCallback(event);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* handle, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(handle);

				switch (action) {
					case GLFW_PRESS:
					{
						KeyPressedEvent event(key, 0);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key);
						data.EventCallback(event);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent event(key, 1);
						data.EventCallback(event);
						break;
					}
				}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* handle, unsigned int keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(handle);
				KeyTypedEvent event(keycode);
				data.EventCallback(event);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* handle, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(handle);

				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event(button);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event(button);
						data.EventCallback(event);
						break;
					}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* handle, double xOffs, double yOffs)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(handle);
				MouseScrolledEvent event((float) xOffs, (float) yOffs);
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* handle, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(handle);
				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});
	}

	void GLWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void GLWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void GLWindow::SetVSync(bool enabled)
	{
		if (enabled) glfwSwapInterval(1);
		else glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool GLWindow::UseVSync() const
	{
		return m_Data.VSync;
	}

}