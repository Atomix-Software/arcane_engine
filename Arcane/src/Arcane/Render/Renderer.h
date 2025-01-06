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

		static void Submit(const Shared<Shader>& shader, const Shared<VertexArray>& vao);

		inline static RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }

	private:
		struct SceneData
		{
			std::vector<Shared<Shader>> Shaders;
			std::unordered_map<Shared<Shader>, std::vector<Shared<VertexArray>>> Objects;

			glm::mat4 ProjectionView;

			int ShaderCount = 0;
			int ObjectCount = 0;
		};

		static SceneData* m_SceneData;
	};
}