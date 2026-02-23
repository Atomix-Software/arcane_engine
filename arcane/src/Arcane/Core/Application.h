#pragma once

#include "Arcane/Core/Base.h"
#include "Arcane/Core/Window.h"
#include "Arcane/Core/LayerStack.h"

#include "Arcane/Events/ApplicationEvent.h"
#include "Arcane/ImGui/ImGuiLayer.h"

namespace Arcane {

	class AE_API Application {
	public:
		Application();
		virtual ~Application() = default;

		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		void OnEvent(Event& e);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClosed(WindowCloseEvent& e);

	private:
		Unique<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;
		LayerStack m_LayerStack;

	private:
		static Application* s_Instance;
	};

	// Define in the Application made with Arcane Engine
	Application* CreateApplication();

}