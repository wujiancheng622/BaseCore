#ifndef NETUTILS_H_
#define NETUTILS_H_

#include "CrossPlatform.h"
#include <vector>

#if defined(WIN32)||defined(WIN64)||defined(WINCE)	
#else
#include <iostream>
#include <string>
using std::string;
using std::vector;
#endif

namespace BaseCore
{
	namespace Net
	{
#if defined(WIN32)||defined(WIN64)||defined(WINCE)	
		DLL_CLASS char * GetIP(void);
		DLL_CLASS int GetMAC(char * mac);
#else
		DLL_CLASS string getLocalIP(char *eth);
		DLL_CLASS std::vector<std::pair<std::string, std::string> > GetAllLocalIP();
#endif
	}
}

#endif NETUTILS_H_