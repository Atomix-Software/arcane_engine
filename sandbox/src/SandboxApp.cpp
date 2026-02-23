#include <Arcane.h>

#include <imgui.h>

class SandboxLayer : public Arcane::Layer
{
public:
	SandboxLayer() :
		Layer("SandboxLayer")
	{

	}

	void OnUpdate() override
	{

	}

	void OnImGuiRender() override
	{

	}

	void OnEvent(Arcane::Event& event) override
	{

	}
};

class Sandbox : public Arcane::Application
{
public:
	Sandbox()
	{
		PushLayer(new SandboxLayer());
	}

	~Sandbox()
	{

	}
};

Arcane::Application* Arcane::CreateApplication()
{
	return new Sandbox();
}