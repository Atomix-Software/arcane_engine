#pragma once

#include <Arcane.h>

#include "editor/AssetExplorer.h"

namespace Grimoire
{
	class EditorLayer : public Arcane::Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() override {}

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		virtual void OnUpdate(Arcane::Timestep ts) override;
		virtual void OnEvent(Arcane::Event& e) override;

	private:
		Arcane::Unique<AssetExplorer> m_Assets;

		Arcane::Shared<Arcane::OrthoCameraController> m_EditorCamera;
		Arcane::Shared <Arcane::Framebuffer> m_Framebuffer;

		bool m_ViewportFocused, m_ViewportHovered;
		glm::vec2 m_ViewportSize;

	};
}