#include <arcpch.h>

#include "Arcane/Core/Input.h"

#include "Arcane/Render/Renderer.h"
#include "Platform/Windows/WindowsInput.h"

namespace Arcane
{
	Unique<Input> Input::s_Instance = Create();

	Unique<Input> Input::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None: ARC_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
		case RenderAPI::API::OpenGL: return CreateUnique<WindowsInput>();
		}

		ARC_CORE_ASSERT(false, "Unknown API selected!");
		return nullptr;
	}
}