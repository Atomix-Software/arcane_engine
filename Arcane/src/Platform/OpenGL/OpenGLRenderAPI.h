#pragma once

#include "Arcane/Render/RenderAPI.h"

namespace Arcane
{
	class OpenGLRenderAPI : public RenderAPI
	{
	public:
		virtual void Init() override;
		virtual void Clear(bool clearDepth) override;

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vao) override;
	};
}