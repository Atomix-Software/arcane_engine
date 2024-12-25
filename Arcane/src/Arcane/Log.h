#pragma once

#include "Core.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <memory>

namespace Arcane
{

	class ARC_API Log
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


#define ARC_CORE_TRACE(...)	   ::Arcane::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ARC_CORE_INFO(...)	   ::Arcane::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ARC_CORE_WARN(...)	   ::Arcane::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ARC_CORE_ERROR(...)	   ::Arcane::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ARC_CORE_CRITICAL(...) ::Arcane::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define ARC_CLIENT_TRACE(...)	 ::Arcane::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ARC_CLIENT_INFO(...)	 ::Arcane::Log::GetClientLogger()->info(__VA_ARGS__)
#define ARC_CLIENT_WARN(...)     ::Arcane::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ARC_CLIENT_ERROR(...)    ::Arcane::Log::GetClientLogger()->error(__VA_ARGS__)
#define ARC_CLIENT_CRITICAL(...) ::Arcane::Log::GetClientLogger()->critical(__VA_ARGS__)