#include <arcpch.h>

#include "Renderer.h"

namespace Arcane
{
	void Renderer::BeginScene()
	{

	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vao)
	{
		vao->Bind();
		RenderCMD::DrawIndexed(vao);
	}
}