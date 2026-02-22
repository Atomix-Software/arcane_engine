#pragma once

#include "Arcane/Events/Event.h"

namespace Arcane
{

	class AE_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height) {
		}

		unsigned int GetWidth() const { return m_Width; }
		unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_TYPE(WindowResize)
		EVENT_CATEGORY(App)
	private:
		unsigned int m_Width, m_Height;
	};

	class AE_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		EVENT_TYPE(WindowClose)
		EVENT_CATEGORY(App)
	};

	class AE_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() = default;

		EVENT_TYPE(AppTick)
		EVENT_CATEGORY(App)
	};

	class AE_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() = default;

		EVENT_TYPE(AppUpdate)
		EVENT_CATEGORY(App)
	};

	class AE_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() = default;

		EVENT_TYPE(AppRender)
		EVENT_CATEGORY(App)
	};

}