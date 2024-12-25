#pragma once

#ifdef ARC_PLATFORM_WINDOWS
	#ifdef ARC_BUILD_DLL
		#define ARC_API __declspec(dllexport)
	#else
		#define ARC_API __declspec(dllimport)
	#endif
#else
	#error We only support Windows!
#endif

#include <memory>

#ifdef ARC_DEBUG
	#define ARC_ENABLE_ASSERTS
#endif

#ifdef ARC_ENABLE_ASSERTS
	#define ARC_ASSERT(x, ...) { if(!(x)) { ARC_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
	#define ARC_CORE_ASSERT(x, ...) { if(!(x)) { ARC_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else 
	#define ARC_ASSERT(x, ...)
	#define ARC_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define ARC_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Arcane
{

	template<typename T>
	using Unique = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Unique<T> CreateUnique(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Shared = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Shared<T> CreateShared(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}

#include "Arcane/Core/Log.h"