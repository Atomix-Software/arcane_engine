#include <arcpch.h>

#include "Renderer.h"

namespace Arcane
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData();

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ProjectionView = camera.GetProjectionView();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vao)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ProjectionView", m_SceneData->ProjectionView);

		vao->Bind();
		RenderCMD::DrawIndexed(vao);
	}
}