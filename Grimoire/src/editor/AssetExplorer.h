#pragma once

#include <filesystem>
#include <iostream>
#include <string>
#include <unordered_map>

namespace Grimoire
{
	enum AssetType : int8_t
	{
		Unsupported = -1,
		Image, Audio, Shader, Text, Model
	};

	struct AssetSelection
	{
		std::string Name;
		std::string FullPath;

		AssetType Type = Unsupported;
		bool IsValid() const { return !FullPath.empty(); }
	};

	class AssetExplorer
	{
	public:
		AssetExplorer(std::string projectDir);
		~AssetExplorer();

		void ImGui();

		inline const std::string GetCurrentDir() const { return m_CurrentDir; }
		inline const std::string GetRootDir() const { return m_RootDir; }

		inline AssetSelection& GetSelection() { return m_Selection; }

	private:
		void Update();

	private:
		std::string m_CurrentDir;
		std::string m_RootDir;

		std::unordered_map<std::string, std::string> m_Directories;
		std::unordered_map<std::string, std::string> m_Files;
		bool m_Loaded;

		AssetSelection m_Selection;
	};

}