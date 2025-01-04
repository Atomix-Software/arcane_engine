#include <Arcane.h>

#include <imgui.h>

class ExampleLayer : public Arcane::Layer
{
public:
	ExampleLayer() :
		Layer("Example") {}

	virtual void OnUpdate() override
	{

	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello, World!");
		ImGui::End();
	}

	virtual void OnEvent(Arcane::Event& event)
	{

	}
};

class Playground : public Arcane::Application
{
public:
	Playground()
	{
		PushLayer(new ExampleLayer());
	}

	~Playground()
	{

	}


};

Arcane::Application* Arcane::CreateApplication()
{
	return new Playground();
}