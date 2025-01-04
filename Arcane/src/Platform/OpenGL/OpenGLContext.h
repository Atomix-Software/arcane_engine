#pragma once

#include "Arcane/Render/GraphicsContext.h"

namespace Arcane
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* winHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_WinHandle;
	};
}