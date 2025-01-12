#pragma once

#include "Arcane/Core/Base.h"

struct GLFWwindow;

namespace Arcane
{
	class ARC_API GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}