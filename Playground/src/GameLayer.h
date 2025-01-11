#pragma once

#include <Arcane.h>

class GameLayer : public Arcane::Layer
{
public:
	GameLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnImGuiRender() override;

	virtual void OnUpdate(Arcane::Timestep ts) override;
	virtual void OnEvent(Arcane::Event& event) override;

private:
	Arcane::OrthoCameraController* m_CamController;
	Arcane::Shared<Arcane::Texture2D> m_Texture, m_Spritesheet;

	Arcane::Shared<Arcane::SubTexture2D> m_Dirt, m_Grass;
};