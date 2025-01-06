#pragma once

#include "Arcane/Core/Core.h"

#include "Arcane/Render/VertexArray.h"

#include <glm/glm.hpp>

namespace Arcane
{
	class ARC_API RenderAPI
	{
	public:
		enum class API
		{
			None = 0,
			OpenGL = 1
		};

	public:
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vao) = 0;

		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;
	};
}