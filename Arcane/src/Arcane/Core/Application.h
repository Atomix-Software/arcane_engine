#pragma once

#include "Arcane/Core/Core.h"
#include "Arcane/Core/Window.h"
#include "Arcane/Core/LayerStack.h"

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

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		Unique<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// Defined application side
	Application* CreateApplication();
}