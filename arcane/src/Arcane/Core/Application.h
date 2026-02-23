#pragma once

#include "Arcane/Core/Base.h"
#include "Arcane/Core/Window.h"
#include "Arcane/Core/LayerStack.h"

#include "Arcane/Events/ApplicationEvent.h"

namespace Arcane {

	class AE_API Application {
	public:
		Application();
		virtual ~Application() = default;

		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		void OnEvent(Event& e);

	private:
		bool OnWindowClosed(WindowCloseEvent& e);

	private:
		Unique<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// Define in the Application made with Arcane Engine
	Application* CreateApplication();

}