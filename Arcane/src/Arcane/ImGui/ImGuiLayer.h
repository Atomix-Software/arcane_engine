#pragma once

#include "Arcane/Core/Layer.h"

#include "Arcane/Events/ApplicationEvent.h"
#include "Arcane/Events/KeyEvent.h"
#include "Arcane/Events/MouseEvent.h"

namespace Arcane
{

	class ARC_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;

		void OnUpdate() override;
		void OnEvent(Event& event) override;

	private:
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleased(MouseButtonReleasedEvent& e);
		bool OnMouseMoved(MouseMovedEvent& e);
		bool OnMouseScrolled(MouseScrolledEvent& e);

		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnKeyReleased(KeyReleasedEvent& e);
		bool OnKeyTyped(KeyTypedEvent& e);

		bool OnWindowResize(WindowResizeEvent& e);

	private:
		float m_Time;
	};

}
