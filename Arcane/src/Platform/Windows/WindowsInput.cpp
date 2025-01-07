#include <arcpch.h>

#include "Platform/Windows/WindowsInput.h"

#include "Arcane/Core/Application.h"

#include <GLFW/glfw3.h>


namespace Arcane
{
	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow()->GetNativeWindow());
		auto state = glfwGetKey(window, keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow()->GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	std::pair<float, float> WindowsInput::GetMousePosImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow()->GetNativeWindow());
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		return { (float) mouseX, (float) mouseY };
	}

	float WindowsInput::GetMouseXImpl()
	{
		auto [x, y] = GetMousePosImpl();
		return x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePosImpl();
		return y;
	}
}