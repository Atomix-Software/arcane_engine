#pragma once

#include "aepch.h"

#include "Arcane/Core/Base.h"
#include "Arcane/Events/Event.h"

namespace Arcane
{

	struct WindowProps
	{
		std::string Title;
		unsigned int Width, Height;

		WindowProps(const std::string& title = "Arcane Engine", unsigned int width = 1280, unsigned height = 720) :
			Title(title), Width(width), Height(height)
		{ }
	};

	class AE_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window Attribs
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool UseVSync() const = 0;

		static Window* Create(const WindowProps& properties = WindowProps());
	};

}