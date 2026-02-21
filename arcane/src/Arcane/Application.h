#pragma once

#include "Base.h"

namespace Arcane {

	class ARC_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// Define in the Application made with Arcane Engine
	Application* CreateApplication();

}