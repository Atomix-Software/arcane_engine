#pragma once

#include "Arcane/Core/Base.h"
#include "Arcane/Core/Layer.h"

#include "Arcane/Events/ApplicationEvent.h"
#include "Arcane/Events/MouseEvent.h"
#include "Arcane/Events/KeyEvent.h"

namespace Arcane
{

	class AE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};

}
