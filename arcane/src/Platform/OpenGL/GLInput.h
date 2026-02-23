#pragma once

#include "Arcane/Core/Input.h"

namespace Arcane
{

	class GLInput : public Input
	{
	protected:
		bool IsKeyPressedImpl(int keycode) override;
		bool IsMouseButtonPressedImpl(int button) override;

		float GetMouseXImpl() override;
		float GetMouseYImpl() override;
		std::pair<float, float> GetMousePositionImpl() override;
	};

}