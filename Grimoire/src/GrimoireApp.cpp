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
			PushLayer(new EditorLayer());
		}
	};

	Application* CreateApplication()
	{
		return new GrimoireApp({ "Arcane Grimoire Editor" });
	}

}