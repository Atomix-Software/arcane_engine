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
	m_Spritesheet = Arcane::Texture2D::Create("assets/textures/blocks.png");

	m_Dirt  = Arcane::SubTexture2D::CreateFromCoords(m_Spritesheet, { 2, 15 }, { 16, 16 });
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

	static bool dockspaceOpen = true;
	static bool opt_fullscreen_persistent = true;
	bool opt_fullscreen = opt_fullscreen_persistent;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}

	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("Dockspace", &dockspaceOpen, window_flags);
	ImGui::PopStyleVar();

	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if(ImGui::MenuItem("Exit")) Arcane::Application::Get().Stop();
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}

	ImGui::Begin("Test", (bool*) true, ImGuiWindowFlags_NoScrollbar);
	ImVec2 size = ImGui::GetWindowSize();
	ImGui::Image(m_Texture->GetRendererID(), ImVec2(size.x, size.y), ImVec2(1, 1), ImVec2(0, 0));
	ImGui::End();

	ImGui::Begin("Settings");
	Arcane::Renderer2D::Statistics stats = Arcane::Renderer2D::GetStats();
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quad Count: %d", stats.QuadCount);

	ImGui::Text("Vertex Count: %d", stats.GetTotalVertexCount());
	ImGui::Text("Index Count: %d", stats.GetTotalIndexCount());
	ImGui::End();

	ImGui::End();
}
