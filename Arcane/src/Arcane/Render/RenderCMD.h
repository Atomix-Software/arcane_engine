#pragma once

#include "RenderAPI.h"

namespace Arcane
{
	class RenderCMD
	{
	public:
		inline static void Init()
		{
			s_RenderAPI->Init();
		}

		inline static void Clear()
		{
			s_RenderAPI->Clear();
		}

		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RenderAPI->SetClearColor(color);
		}

		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_RenderAPI->SetViewport(x, y, width, height);
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vao)
		{
			s_RenderAPI->DrawIndexed(vao);
		}

	private:
		static RenderAPI* s_RenderAPI;

	};
}