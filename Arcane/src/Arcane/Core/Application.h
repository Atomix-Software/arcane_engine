#pragma once

#include "Arcane/Core/Core.h"
#include "Arcane/Core/Window.h"
#include "Arcane/Core/LayerStack.h"

#include "Arcane/Events/ApplicationEvent.h"

#include "Arcane/Render/Renderer.h"

#include "Arcane/ImGui/ImGuiLayer.h"

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

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		Unique<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

	private:
		static Application* s_Instance;

	};

	// Defined application side
	Application* CreateApplication();
}