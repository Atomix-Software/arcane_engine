#include "AssetExplorer.h"

#include <imgui.h>
#include <Arcane.h>
#include <Arcane/Core/Log.h>

namespace Grimoire
{
    AssetExplorer::AssetExplorer(std::string projectDir) :
        m_Loaded(false)
    {
        m_RootDir = projectDir;
        m_CurrentDir = projectDir;

        Update();
    }

	AssetExplorer::~AssetExplorer()
	{

	}

	void AssetExplorer::Update()
	{
        namespace fs = std::filesystem;
        fs::path currPath = fs::path(m_CurrentDir).lexically_normal();

        m_Directories.clear();
        m_Files.clear();

        try
        {
            for (const auto& entry : fs::directory_iterator{ currPath })
            {
                const auto& path = entry.path();
                std::string name = path.filename().string();
                std::string fullPath = path.lexically_normal().string();

                if (entry.is_directory())
                    m_Directories.emplace(name, fullPath);
                else if (entry.is_regular_file())
                    m_Files.emplace(name, fullPath);
            }
        }
        catch (const fs::filesystem_error& ex)
        {
            ARC_ERROR("Error during file iteration: {0}", ex.what());
        }

        m_Loaded = true;
	}

	void AssetExplorer::ImGui()
	{
		namespace fs = std::filesystem;

		fs::path currentPath = fs::path(m_CurrentDir).lexically_normal();
		fs::path rootPath = fs::path(m_RootDir).lexically_normal();

		ImGui::Begin("Assets");
		bool clickedSomething = false;

		if (m_Loaded)
		{
			// Only show back button if current path is NOT root
			if (!fs::equivalent(currentPath, rootPath))
			{
				if (ImGui::Button("\\"))
				{
					fs::path parent = currentPath.parent_path().lexically_normal();

					// Prevent navigating above project root
					if (fs::equivalent(parent, rootPath) || parent.string().starts_with(rootPath.string()))
					{
						m_CurrentDir = parent.string();
						m_Loaded = false;
						Update();

						ImGui::End();
						return;
					}
				}
			}

			// Show directory buttons
			for (auto& [dirName, fullPath] : m_Directories)
			{
				std::string label = dirName + "\\";
				if (ImGui::Button(label.c_str()))
				{
					m_CurrentDir = fs::path(fullPath).lexically_normal().string();
					m_Loaded = false;
					Update();

					ImGui::End();
					return;
				}

				if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0))
					clickedSomething = true;
			}

			// Show file names
			for (auto& [fileName, fullPath] : m_Files)
			{
				bool selected = (m_Selection.FullPath == fullPath);
				if (ImGui::Selectable(fileName.c_str(), selected))
				{
					m_Selection = {
						fileName,
						fullPath,
						// Detect type (basic extension check)
						[](const std::string& ext) -> AssetType {
							std::string lowerExt = ext;
							std::transform(lowerExt.begin(), lowerExt.end(), lowerExt.begin(), ::tolower);

							if (lowerExt == ".png"  || lowerExt == ".jpg"  || lowerExt == ".jpeg") return Image;
							if (lowerExt == ".wav"  || lowerExt == ".ogg"  || lowerExt == ".mp3")  return Audio;
							if (lowerExt == ".txt"  || lowerExt == ".json" || lowerExt == ".xml"    || lowerExt == ".ini")  return Text;
							if (lowerExt == ".vert" || lowerExt == ".frag" || lowerExt == ".shader" || lowerExt == ".glsl" || lowerExt == ".hlsl") return Shader;
							if (lowerExt == ".obj"  || lowerExt == ".fbx"  || lowerExt == ".gltf"   || lowerExt == ".glb"  || lowerExt == ".dae" || lowerExt == ".3ds" || lowerExt == ".blend" || lowerExt == ".stl") return Model;
							return Unsupported;
						}(std::filesystem::path(fullPath).extension().string())
					};

					clickedSomething = true;
				}

				if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0))
					clickedSomething = true;
			}
		}
		
		// Clear selection if clicking on background
		if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(0) && !clickedSomething)
		{
			m_Selection = {}; // Reset to default
		}

		ImGui::End();

		ImGui::Begin("File View");

		if (m_Selection.IsValid())
		{
			std::string path = m_Selection.FullPath.substr(0, m_Selection.FullPath.find_last_of('\\') + 1);
			ImGui::Text("Path: %s", path.c_str());
			ImGui::Text("Name: %s", m_Selection.Name.c_str());

			std::string type = "";
			switch(m_Selection.Type)
			{
				case AssetType::Image:
				{
					type = "Image";
					break;
				}

				case AssetType::Audio:
				{
					type = "Audio";
					break;
				}

				case AssetType::Shader:
				{
					type = "Shader";
					break;
				}

				case AssetType::Text:
				{
					type = "Text";
					break;
				}

				case AssetType::Unsupported:
				{
					type = "Unsupported";
					break;
				}
			}

			ImGui::Text("Type: %s", type.c_str());
		}

		ImGui::End();

	}
}