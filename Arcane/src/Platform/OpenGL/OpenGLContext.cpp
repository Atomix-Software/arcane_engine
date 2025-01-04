#include <arcpch.h>

#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Arcane
{
	static bool s_GLADInitialized = false;

	OpenGLContext::OpenGLContext(GLFWwindow* winHandle) :
		m_WinHandle(winHandle)
	{
		ARC_CORE_ASSERT(winHandle, "Window Handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WinHandle);
		if (!s_GLADInitialized)
		{
			int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
			ARC_CORE_ASSERT(success, "Could not initialize OpenGL!");

			s_GLADInitialized = true;
		}
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WinHandle);
	}
}