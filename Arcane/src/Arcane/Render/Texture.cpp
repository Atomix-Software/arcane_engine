#include <arcpch.h>

#include "Texture.h"

#include "Arcane/Render/Renderer.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace Arcane
{
	Shared<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None: ARC_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
		case RenderAPI::API::OpenGL: return CreateShared<OpenGLTexture2D>(path);
		}

		ARC_CORE_ASSERT(false, "Unknown API selected!");
		return nullptr;
	}
}