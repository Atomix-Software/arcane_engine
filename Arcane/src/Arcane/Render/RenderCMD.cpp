#include <arcpch.h>

#include "RenderCMD.h"

#include "Platform/OpenGL/OpenGLRenderAPI.h"

namespace Arcane
{
	RenderAPI* RenderCMD::s_RenderAPI = new OpenGLRenderAPI();
}