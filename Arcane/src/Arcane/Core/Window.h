#pragma once

#include <arcpch.h>

#include "Arcane/Core/Base.h"
#include "Arcane/Events/Event.h"

namespace Arcane
{
	struct ARC_API WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Arcane Engine", unsigned int width = 1280, unsigned int height = 720) :
			Title(title), Width(width), Height(height) {}
	};

	class ARC_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void PushEvent(Event& event) = 0;

		// Window Attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Unique<Window> Create(const WindowProps& props = WindowProps());
	};
}