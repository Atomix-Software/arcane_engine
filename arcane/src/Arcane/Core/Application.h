#pragma once

#include "Base.h"

namespace Arcane {

	class AE_API Application {
	public:
		Application() = default;
		virtual ~Application() = default;

		void Run();
	};

	// Define in the Application made with Arcane Engine
	Application* CreateApplication();

}