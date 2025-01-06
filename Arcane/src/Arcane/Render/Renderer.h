#pragma once

#include "RenderCMD.h"

#include "Arcane/Render/Shader.h"
#include "Arcane/Render/Camera.h"

namespace Arcane
{
	class Renderer
	{
	public:
		struct SceneData
		{
			std::vector<Shared<Shader>> Shaders;
			std::unordered_map<Shared<Shader>, std::vector<std::pair<Shared<VertexArray>, glm::mat4>>> Objects;

			glm::mat4 ProjectionView;

			int ShaderCount = 0;
			int ObjectCount = 0;

			bool Rendering = false;
		};

	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Shared<Shader>& shader, const Shared<VertexArray>& vao, const glm::vec3 position, float rotation = 0.0f, float scale = 1.0f);
		static void Submit(const Shared<Shader>& shader, const Shared<VertexArray>& vao, const glm::mat4& transform = glm::mat4(1.0));

		inline static RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }

		inline static const SceneData& GetSceneData() { return *m_SceneData; }

	private:
		static SceneData* m_SceneData;

	};
}