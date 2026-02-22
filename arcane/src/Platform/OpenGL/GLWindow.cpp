#include "aepch.h"

#include "Arcane/Core/Log.h"
#include "Platform/OpenGL/GLWindow.h"

namespace Arcane
{

	static bool s_GLFWInitialized = false;

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

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int) m_Data.Width, (int) m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
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