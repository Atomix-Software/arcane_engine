#pragma once

#include <memory>

#include "Base.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Arcane
{
	class AE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

#ifndef AE_RELEASE
	// Log macros for Engine use
	#define AE_CORE_INFO(...)  ::Arcane::Log::GetCoreLogger()->info(__VA_ARGS__)
	#define AE_CORE_TRACE(...) ::Arcane::Log::GetCoreLogger()->trace(__VA_ARGS__)
	#define AE_CORE_WARN(...)  ::Arcane::Log::GetCoreLogger()->warn(__VA_ARGS__)
	#define AE_CORE_ERROR(...) ::Arcane::Log::GetCoreLogger()->error(__VA_ARGS__)

	// Log macros for Application use
	#define AE_INFO(...)  ::Arcane::Log::GetClientLogger()->info(__VA_ARGS__)
	#define AE_TRACE(...) ::Arcane::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define AE_WARN(...)  ::Arcane::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define AE_ERROR(...) ::Arcane::Log::GetClientLogger()->error(__VA_ARGS__)
#else
	// Log macros for Engine use
	#define AE_CORE_INFO(...)
	#define AE_CORE_TRACE(...)
	#define AE_CORE_WARN(...)
	#define AE_CORE_ERROR(...)

	// Log macros for Application use
	#define AE_INFO(...)
	#define AE_TRACE(...)
	#define AE_WARN(...)
	#define AE_ERROR(...)
#endif