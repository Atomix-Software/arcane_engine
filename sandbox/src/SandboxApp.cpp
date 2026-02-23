#include <Arcane.h>

class SandboxLayer : public Arcane::Layer
{
public:
	SandboxLayer() :
		Layer("SandboxLayer")
	{

	}

	void OnUpdate() override
	{
		AE_INFO("{0}::Update", GetName());
	}

	void OnEvent(Arcane::Event& event) override
	{
		AE_TRACE(event.ToString());
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