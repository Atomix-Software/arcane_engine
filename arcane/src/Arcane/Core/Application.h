#pragma once

#include "Arcane/Core/Base.h"
#include "Arcane/Core/Window.h"

#include "Arcane/Events/Event.h"

namespace Arcane {

	class AE_API Application {
	public:
		Application();
		virtual ~Application() = default;

		void Run();
	private:
		Unique<Window> m_Window;
		bool m_Running = true;
	};

	// Define in the Application made with Arcane Engine
	Application* CreateApplication();

}