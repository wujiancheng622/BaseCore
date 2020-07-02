// #ifndef _PLATFORM_H_
// #define _PLATFORM_H_

#if defined(WIN32)||defined(WIN64)||defined(WINCE)	
#define  DLL_CLASS _declspec(dllexport)
#include <windows.h>
#else
#define  DLL_CLASS
#endif

//#endif//_PLATFORM_H_

