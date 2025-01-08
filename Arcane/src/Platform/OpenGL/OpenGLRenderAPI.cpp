#include <arcpch.h>

#include "Platform/OpenGL/OpenGLRenderAPI.h"

#include <glad/glad.h>

namespace Arcane
{
	void OpenGLRenderAPI::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRenderAPI::Clear(bool clearDepth)
	{
		GLenum clearMask = GL_COLOR_BUFFER_BIT;
		if (clearDepth) clearMask |= GL_DEPTH_BUFFER_BIT;

		glClear(clearMask);
	}

	void OpenGLRenderAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRenderAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRenderAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vao, uint32_t count)
	{
		uint32_t indexCount = count != 0 ? count : vao->GetIndexBuffer()->GetCount();
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}