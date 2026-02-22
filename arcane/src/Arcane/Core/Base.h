#pragma once

#include <memory>

#ifdef AE_PLAT_WINDOWS
	#ifdef AE_BUILD_DLL
		#define AE_API __declspec(dllexport)
	#else
		#define AE_API __declspec(dllimport)
	#endif

	#ifdef AE_DEBUG
		#define AE_DEBUGBREAK() __debugbreak()
		#define AE_ENABLE_ASSERTS
	#else
		#define AE_DEBUGBREAK()
	#endif
#else
	#error Arcane Engine currently only supports Windows!
#endif

#define AE_EXPAND_MACRO(x) x
#define AE_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

#define AE_BIND_EVENT(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Arcane {

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
#include "Arcane/Core/Assert.h"