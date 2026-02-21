#pragma once

#ifdef ARC_PLAT_WINDOWS
	#ifdef ARC_BUILD_DLL
		#define ARC_API __declspec(dllexport)
	#else
		#define ARC_API __declspec(dllimport)
	#endif
#else
	#error Arcane Engine currently only supports Windows!
#endif