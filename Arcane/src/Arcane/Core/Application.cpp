#include <arcpch.h>

#include "Arcane/core/Application.h"
#include "Arcane/core/Log.h"

#include <glad/glad.h>

namespace Arcane
{

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		ARC_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = Unique<Window>(Window::Create());
		m_Window->SetEventCallback(ARC_BIND_EVENT_FN(Application::OnEvent));
	}

	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(ARC_BIND_EVENT_FN(Application::OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return false;
	}

	void Application::Run()
	{
		glClearColor(0.75f, 0.0f, 0.75f, 1.0f);

		while (m_Running)
		{
			glClear(GL_COLOR_BUFFER_BIT);

			for (auto layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
	}

}