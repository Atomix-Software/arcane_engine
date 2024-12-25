#pragma once

#include "Core.h"

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