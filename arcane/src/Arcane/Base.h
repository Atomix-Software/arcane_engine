#pragma once

#ifdef AE_PLAT_WINDOWS
	#ifdef AE_BUILD_DLL
		#define AE_API __declspec(dllexport)
	#else
		#define AE_API __declspec(dllimport)
	#endif
#else
	#error Arcane Engine currently only supports Windows!
#endif