#include "Layer2D.h"

#include <imgui.h>

Layer2D::Layer2D() :
	Layer("Test2D")
{
	uint32_t width = Arcane::Application::Get().GetWindow()->GetWidth();
	uint32_t height = Arcane::Application::Get().GetWindow()->GetHeight();
	m_CamController = new Arcane::OrthoCameraController((float)width / (float)height);
}

void Layer2D::OnAttach()
{
	Arcane::Renderer2D::Init();
}

void Layer2D::OnDetach()
{
	Arcane::Renderer2D::Shutdown();
}

void Layer2D::OnUpdate(Arcane::Timestep ts)
{
	m_CamController->OnUpdate(ts);

	Arcane::RenderCMD::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
	Arcane::RenderCMD::Clear(true);

	Arcane::Renderer2D::BeginScene(*m_CamController->GetCamera());

	Arcane::Renderer2D::EndScene();
}

void Layer2D::OnEvent(Arcane::Event& event)
{
	m_CamController->OnEvent(event);
}

void Layer2D::OnImGuiRender()
{

}
