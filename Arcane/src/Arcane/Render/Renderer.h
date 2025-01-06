#pragma once

#include "RenderCMD.h"

namespace Arcane
{
	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vao);

		inline static RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }
	};
}