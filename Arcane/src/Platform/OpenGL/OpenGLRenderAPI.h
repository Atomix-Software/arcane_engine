#pragma once

#include "Arcane/Render/RenderAPI.h"

namespace Arcane
{
	class OpenGLRenderAPI : public RenderAPI
	{
	public:
		virtual void Init() override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vao) override;
	};
}