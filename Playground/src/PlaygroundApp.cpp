#include <Arcane.h>

class ExampleLayer : public Arcane::Layer
{
public:
	ExampleLayer() :
		Layer("Example") {}

	void OnUpdate() override
	{

	}

	void OnEvent(Arcane::Event& event)
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