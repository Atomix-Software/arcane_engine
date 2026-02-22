#include "aepch.h"
#include "Application.h"

namespace Arcane {

	Application::Application()
	{
		m_Window = Unique<Window>(Window::Create());
	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}

}