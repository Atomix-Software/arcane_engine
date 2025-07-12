#include <Arcane.h>
#include <Arcane/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Arcane
{
	class GrimoireApp : public Application
	{
	public:
		GrimoireApp(const WindowProps& props) :
			Application(props)
		{
			m_Editor = new Grimoire::EditorLayer();
			PushLayer(m_Editor);
		}

		~GrimoireApp()
		{
			Application::~Application();
			PopLayer(m_Editor);
		}

	private:
		Layer* m_Editor;
	};

	Application* CreateApplication()
	{
		WindowProps props;
		props.Title = "Arcane Engine";
		props.Resizable = true;

		return new GrimoireApp(props);
	}

}