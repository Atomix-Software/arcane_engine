#include <Arcane.h>

#include <iostream>

class Playground : public Arcane::Application
{
public:
	Playground()
	{
		ARC_TRACE("Application Created!");
	}

	~Playground()
	{

	}


};

Arcane::Application* Arcane::CreateApplication()
{
	return new Playground();
}