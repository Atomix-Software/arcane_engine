#include "EditorLayer.h"

#include <imgui.h>

#include <tinyfiledialogs.h>
#include <tinyxml/tinyxml2.h>

namespace Grimoire
{
	void LoadProject(const std::string& filepath, std::string& outName, std::string& outAssetsPath, std::string& outScriptsPath)
	{
		tinyxml2::XMLDocument doc;
		if (doc.LoadFile(filepath.c_str()) != tinyxml2::XML_SUCCESS)
		{
			ARC_ERROR("Failed to load project file: {0}", filepath);
			return;
		}

		auto* root = doc.FirstChildElement("Project");
		if (!root) return;

		const char* nameAttr = root->Attribute("name");
		if (nameAttr) outName = nameAttr;

		if (auto* assets = root->FirstChildElement("Assets"))
			outAssetsPath = assets->GetText() ? assets->GetText() : "";

		if (auto* scripts = root->FirstChildElement("Scripts"))
			outScriptsPath = scripts->GetText() ? scripts->GetText() : "";
	}

	EditorLayer::EditorLayer() :
		Layer("EditorLayer")
	{
		uint32_t width = Arcane::Application::Get().GetWindow()->GetWidth();
		uint32_t height = Arcane::Application::Get().GetWindow()->GetHeight();
		m_EditorCamera = Arcane::CreateShared<Arcane::OrthoCameraController>((float)width / (float)height);

		m_ViewportFocused = false;
		m_ViewportHovered = false;
		m_ViewportSize = { (float) width, (float) height };
	}

	void EditorLayer::OnAttach()
	{
		ARC_PROFILE_FUNCTION();

		Arcane::Renderer2D::Init();

		m_Assets = Arcane::CreateUnique<AssetExplorer>();

		uint32_t width = Arcane::Application::Get().GetWindow()->GetWidth();
		uint32_t height = Arcane::Application::Get().GetWindow()->GetHeight();
		Arcane::FramebufferSpec frameBufferSpec;
		frameBufferSpec.Width  = width;
		frameBufferSpec.Height = height;

		m_Framebuffer = Arcane::Framebuffer::Create(frameBufferSpec);
	}

	void EditorLayer::OnDetach()
	{
		Arcane::Renderer2D::Shutdown();
	}

	void EditorLayer::OnUpdate(Arcane::Timestep ts)
	{
		ARC_PROFILE_FUNCTION();

		if(m_ViewportFocused)
			m_EditorCamera->OnUpdate(ts);

		Arcane::Renderer2D::ResetStats();

		m_Framebuffer->Bind();
		Arcane::RenderCMD::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
		Arcane::RenderCMD::Clear(true);

		Arcane::Renderer2D::BeginScene(*m_EditorCamera->GetCamera());

		Arcane::Renderer2D::EndScene();
		m_Framebuffer->Unbind();
	}

	void EditorLayer::OnEvent(Arcane::Event& e)
	{
		m_EditorCamera->OnEvent(e);
	}

	void EditorLayer::OnImGuiRender()
	{
		ARC_PROFILE_FUNCTION();

#pragma region Dockspace Set Up
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

		// Setting ImGui up to use Docking
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}
#pragma endregion

		static char projectName[128] = "NewProject";
		static std::string selectedDirectory = "";
		static bool openedDialog = false;
		static bool triggerNewProjectPopup = false;


#pragma region Menu Bar
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New Project"))
					triggerNewProjectPopup = true;

				if (ImGui::MenuItem("Open Project"))
				{
					const char* filters[] = { "*.arcproj" };
					const char* path = tinyfd_openFileDialog("Open .arcproj", "", 1, filters, "Arcane Project", 0);
					if (path)
					{
						std::string projectNameFromFile, assetsFromFile, scriptsFromFile;
						LoadProject(path, projectNameFromFile, assetsFromFile, scriptsFromFile);

						if (!assetsFromFile.empty() && !scriptsFromFile.empty())
						{
							std::filesystem::path projDir = std::filesystem::path(path).parent_path();
							m_Assets->SetNewRoot(projDir.string());
							ARC_INFO("Loaded project: {0} at {1}", projectNameFromFile, path);
						}
					}
				}

				if (ImGui::MenuItem("Close Project"))
				{
					if (!m_Assets->GetRootDir().empty())
					{
						std::string rootDir = m_Assets->GetRootDir();
						m_Assets->SetNewRoot("");
						ARC_INFO("Closed project: {0}", rootDir.substr(rootDir.find_last_of('\\') + 1, rootDir.size()));
					}
				}

				if (ImGui::MenuItem("Exit"))
					Arcane::Application::Get().Stop();

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		if (triggerNewProjectPopup) 
		{
			strcpy_s(projectName, "NewProject");
			selectedDirectory.clear();
			ImGui::OpenPopup("New Project");

			triggerNewProjectPopup = false;
		}
#pragma endregion


#pragma region New Project Window
		ImGui::SetNextWindowSize(ImVec2(400, 200));
		ImGui::SetNextWindowFocus();

		if (ImGui::BeginPopupModal("New Project", NULL, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::InputText("Project Name", projectName, IM_ARRAYSIZE(projectName));

			if (ImGui::Button("Select Folder"))
			{
				const char* folder = tinyfd_selectFolderDialog("Choose Project Location", "");
				if (folder)
					selectedDirectory = folder;
			}

			ImGui::SameLine();
			ImGui::Text("%s", selectedDirectory.empty() ? "No directory selected." : selectedDirectory.c_str());

			if (ImGui::Button("Create"))
			{
				if (strlen(projectName) > 0 && !selectedDirectory.empty())
				{
					std::filesystem::path projectDir = std::filesystem::path(selectedDirectory) / projectName;
					std::filesystem::create_directories(projectDir);

					std::filesystem::path assetsDir = projectDir / "assets";
					std::filesystem::create_directories(assetsDir);

					std::filesystem::path scriptDir = projectDir / "scripts";
					std::filesystem::create_directories(scriptDir);

					std::filesystem::path projFile = projectDir / (std::string(projectName) + ".arcproj");

					tinyxml2::XMLDocument doc;
					auto* decl = doc.NewDeclaration();
					doc.InsertFirstChild(decl);

					auto* root = doc.NewElement("Project");
					root->SetAttribute("name", projectName);
					doc.InsertEndChild(root);

					auto* assets = doc.NewElement("Assets");
					assets->SetText("assets");
					root->InsertEndChild(assets);

					auto* scripts = doc.NewElement("Scripts");
					scripts->SetText("scripts");
					root->InsertEndChild(scripts);

					doc.SaveFile(projFile.string().c_str());

					ARC_INFO("Created new project at: {0}", projFile.string());

					ImGui::CloseCurrentPopup();
					m_Assets->SetNewRoot(projectDir.string());
				}
			}

			ImGui::SameLine();
			if (ImGui::Button("Cancel"))
				ImGui::CloseCurrentPopup();

			ImGui::EndPopup();
		}

#pragma endregion

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.0f, 0.0f });
		if (ImGui::Begin("Viewport"))
		{
			m_ViewportFocused = ImGui::IsWindowFocused();
			m_ViewportHovered = ImGui::IsWindowHovered();
			Arcane::Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);

			uint32_t textureID = m_Framebuffer->GetColorAttRendererID();
			ImVec2 viewportSize = ImGui::GetContentRegionAvail();

			if (m_ViewportSize != *((glm::vec2*)&viewportSize) && (viewportSize.x > 0 && viewportSize.y > 0))
			{
				m_ViewportSize = { viewportSize.x, viewportSize.y };
				m_EditorCamera->OnResize(m_ViewportSize.x, m_ViewportSize.y);
				m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			}

			ImGui::Image(textureID, *((ImVec2*)&m_ViewportSize), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));
		}
		else {
			Arcane::Application::Get().GetImGuiLayer()->BlockEvents(true);
		}
		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::Begin("Scene");
		// TODO: Implement Scene Editor Window
		ImGui::End();

		m_Assets->ImGui();

		ImGui::Begin("Inspector"); 
		
		ImGui::End();

		ImGui::Begin("2D Renderer Stats");
		Arcane::Renderer2D::Statistics stats = Arcane::Renderer2D::GetStats();
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quad Count: %d", stats.QuadCount);

		ImGui::Text("Vertex Count: %d", stats.GetTotalVertexCount());
		ImGui::Text("Index Count: %d", stats.GetTotalIndexCount());
		ImGui::End();

		ImGui::End();
	}

}