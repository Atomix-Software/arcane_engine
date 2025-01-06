#pragma once

#include "RenderCMD.h"

#include "Arcane/Render/Shader.h"
#include "Arcane/Render/Camera.h"

namespace Arcane
{
	class Renderer
	{
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vao);

		inline static RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ProjectionView;
		};

		static SceneData* m_SceneData;
	};
}