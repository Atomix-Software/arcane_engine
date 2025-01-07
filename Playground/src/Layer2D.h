#pragma once

#include <Arcane.h>

class Layer2D : public Arcane::Layer
{
public:
	Layer2D();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnImGuiRender() override;

	virtual void OnUpdate(Arcane::Timestep ts) override;
	virtual void OnEvent(Arcane::Event& event) override;

private:
	Arcane::OrthoCameraController* m_CamController;
};