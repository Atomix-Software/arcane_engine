#pragma once

#include "Arcane/Core/Core.h"

#include "Arcane/Events/Event.h"
#include "Arcane/Events/ApplicationEvent.h"

namespace Arcane
{

	class ARC_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// Defined application side
	Application* CreateApplication();
}