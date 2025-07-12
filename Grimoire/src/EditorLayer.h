#pragma once

#include <Arcane.h>

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
		Arcane::Shared<Arcane::OrthoCameraController> m_CamController;
		Arcane::Shared<Arcane::Texture2D> m_Spritesheet;
		Arcane::Shared <Arcane::Framebuffer> m_Framebuffer;

		Arcane::Shared<Arcane::SubTexture2D> m_Dirt, m_Grass;

		bool m_ViewportFocused, m_ViewportHovered;
		glm::vec2 m_ViewportSize;

	};
}