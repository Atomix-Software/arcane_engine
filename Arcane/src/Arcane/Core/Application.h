#pragma once

#include "Arcane/Core/Base.h"
#include "Arcane/Core/Window.h"
#include "Arcane/Core/LayerStack.h"
#include "Arcane/Core/Timestep.h"

#include "Arcane/Events/ApplicationEvent.h"

#include "Arcane/Render/Renderer.h"

#include "Arcane/ImGui/ImGuiLayer.h"

namespace Arcane
{

	class ARC_API Application
	{
	public:
		Application(WindowProps winProps = WindowProps());
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline const Unique<Window>& GetWindow() const { return m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		Unique<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;

	};

	// Defined application side
	Application* CreateApplication();
}