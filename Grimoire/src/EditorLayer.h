#pragma once

#include <Arcane.h>

namespace Arcane
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		virtual void OnUpdate(Timestep ts) override;
		virtual void OnEvent(Event& e) override;

	private:
		Arcane::OrthoCameraController* m_CamController;
		Arcane::Shared<Arcane::Texture2D> m_Texture, m_Spritesheet;

		Arcane::Shared<Arcane::SubTexture2D> m_Dirt, m_Grass;
	};
}