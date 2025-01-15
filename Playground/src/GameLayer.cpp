#include "GameLayer.h"

#include <imgui.h>

GameLayer::GameLayer() :
	Layer("Test2D")
{
	uint32_t width = Arcane::Application::Get().GetWindow()->GetWidth();
	uint32_t height = Arcane::Application::Get().GetWindow()->GetHeight();
	m_CamController = new Arcane::OrthoCameraController((float)width / (float)height);
}

GameLayer::~GameLayer()
{
	delete m_CamController;
}

void GameLayer::OnAttach()
{
	ARC_PROFILE_FUNCTION();
	m_Spritesheet = Arcane::Texture2D::Create("assets/textures/blocks.png");

	m_Dirt = Arcane::SubTexture2D::CreateFromCoords(m_Spritesheet, { 2, 15 }, { 16, 16 });
	m_Grass = Arcane::SubTexture2D::CreateFromCoords(m_Spritesheet, { 0, 15 }, { 16, 16 });

}

void GameLayer::OnDetach()
{
	ARC_PROFILE_FUNCTION();
}

void GameLayer::OnUpdate(Arcane::Timestep ts)
{
	ARC_PROFILE_FUNCTION();
	Arcane::Renderer2D::ResetStats();
	m_CamController->OnUpdate(ts);
	
	Arcane::RenderCMD::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
	Arcane::RenderCMD::Clear(true);

	Arcane::Renderer2D::BeginScene(*m_CamController->GetCamera());

	constexpr int size = 25;
	constexpr glm::vec2 scale = { 0.5f, 0.5f };
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			glm::vec2 position = { (x * scale.x) - (size * scale.x) / 2, (y * scale.y) - (size * scale.y) / 2 };
			if ((x + y) % 2 == 0) Arcane::Renderer2D::DrawQuad(position, scale, m_Grass);
			else  Arcane::Renderer2D::DrawQuad(position, scale, m_Dirt);
		}
	}

	Arcane::Renderer2D::EndScene();
}

void GameLayer::OnEvent(Arcane::Event& event)
{
	m_CamController->OnEvent(event);
}

void GameLayer::OnImGuiRender()
{
	ARC_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	Arcane::Renderer2D::Statistics stats = Arcane::Renderer2D::GetStats();
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quad Count: %d", stats.QuadCount);

	ImGui::Text("Vertex Count: %d", stats.GetTotalVertexCount());
	ImGui::Text("Index Count: %d", stats.GetTotalIndexCount());
	ImGui::End();
}
