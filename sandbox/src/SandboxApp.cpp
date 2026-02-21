#include <Arcane.h>

class Sandbox : public Arcane::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Arcane::Application* Arcane::CreateApplication()
{
	return new Sandbox();
}