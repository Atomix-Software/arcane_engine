#include <arcpch.h>

#include "Renderer.h"

namespace Arcane
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData();

    void Renderer::BeginScene(OrthographicCamera& camera)
    {
        m_SceneData->ShaderCount = 0;
        m_SceneData->Objects.clear();

        m_SceneData->ProjectionView = camera.GetProjection() * camera.GetView();
    }

    void Renderer::EndScene()
    {
        for (Shared<Shader> shader : m_SceneData->Shaders)
        {
            shader->Bind();
            shader->UploadUniformMat4("u_ProjectionView", m_SceneData->ProjectionView);

            const auto& objects = m_SceneData->Objects[shader];
            for (const auto& obj : objects)
            {
                obj->Bind();
                RenderCMD::DrawIndexed(obj);
            }
        }

        m_SceneData->Shaders.clear();
    }

    void Renderer::Submit(const Shared<Shader>& shader, const Shared<VertexArray>& vao)
    {
        // Add shader if not already in the list
        if (std::find(m_SceneData->Shaders.begin(), m_SceneData->Shaders.end(), shader) == m_SceneData->Shaders.end())
            m_SceneData->Shaders.push_back(shader);

        // Associate the VAO with the shader
        m_SceneData->Objects[shader].push_back(vao);
    }
}