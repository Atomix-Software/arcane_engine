#pragma once

#include "Arcane/Core/Base.h"
#include "Arcane/Events/Event.h"

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