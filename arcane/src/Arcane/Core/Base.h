#pragma once

#include <memory>

#ifdef AE_PLAT_WINDOWS
	#ifdef AE_BUILD_DLL
		#define AE_API __declspec(dllexport)
	#else
		#define AE_API __declspec(dllimport)
	#endif
#else
	#error Arcane Engine currently only supports Windows!
#endif

#define BIT(x) (1 << x)

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