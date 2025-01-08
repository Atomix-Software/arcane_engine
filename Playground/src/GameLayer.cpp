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
}

void GameLayer::OnDetach()
{
	ARC_PROFILE_FUNCTION();
}

void GameLayer::OnUpdate(Arcane::Timestep ts)
{
	ARC_PROFILE_FUNCTION();
	m_CamController->OnUpdate(ts);
	
	Arcane::RenderCMD::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
	Arcane::RenderCMD::Clear(true);

	Arcane::Renderer2D::BeginScene(*m_CamController->GetCamera());

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

	//for (auto& result : m_ProfileResults)
	//{
	//	char label[50];
	//	strcpy(label, "%.3fms   ");
	//	strcat(label, result.Name);
	//
	//	ImGui::Text(label, result.Time);
	//}
	//m_ProfileResults.clear();

	ImGui::End();
}
