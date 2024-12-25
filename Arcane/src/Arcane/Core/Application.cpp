#include <arcpch.h>

#include "Arcane/core/Application.h"
#include "Arcane/core/Log.h"

namespace Arcane
{

	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		ARC_TRACE(e.ToString());

		while (true)
		{

		}
	}

}