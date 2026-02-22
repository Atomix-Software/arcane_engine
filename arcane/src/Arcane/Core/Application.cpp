#include "aepch.h"
#include "Application.h"

namespace Arcane {

	Application::Application()
	{
		m_Window = Unique<Window>(Window::Create());
		m_Window->SetEventCallback(AE_BIND_EVENT(Application::OnEvent));
	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(AE_BIND_EVENT(Application::OnWindowClosed));
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}