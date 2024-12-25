#include <iostream>

#include <Arcane.h>

class Playground : public Arcane::Application
{
public:
	Playground()
	{

	}

	~Playground()
	{

	}


};

Arcane::Application* Arcane::CreateApplication()
{
	return new Playground();
}