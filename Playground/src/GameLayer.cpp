#include "GameLayer.h"

#include <imgui.h>

GameLayer::GameLayer() :
	Layer("Test2D")
{
	uint32_t width = Arcane::Application::Get().GetWindow()->GetWidth();
	uint32_t height = Arcane::Application::Get().GetWindow()->GetHeight();
	m_CamController = new Arcane::OrthoCameraController((float)width / (float)height);
}

void GameLayer::OnAttach()
{
	ARC_PROFILE_FUNCTION();
	m_Texture = Arcane::Texture2D::Create("assets/textures/whoa.png");
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
	Arcane::Renderer2D::DrawRotatedQuad({ 0, 0, -0.1 }, { 1, 1 }, 45, { 0, 0, 1, 1 });
	Arcane::Renderer2D::DrawQuad({ 0, 0, 0 }, { 1, 1 }, m_Texture);
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
