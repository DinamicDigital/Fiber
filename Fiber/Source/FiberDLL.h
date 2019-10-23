#pragma once

#ifdef FIBER_EXPORTS
	#define FIBER_API __declspec(dllexport)
#else
	#define FIBER_API __declspec(dllimport)
#endif
