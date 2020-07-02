#ifndef OSUTIL_H_
#define OSUTIL_H_

#include "CrossPlatform.h"

#include <list>
#include <string>
using std::string;
using std::list;

namespace BaseCore
{
	namespace Common
	{		
		DLL_CLASS int ReadDirList(const char *basePath, list<string> &dirs);
		DLL_CLASS int ReadFileList(const char *basePath, list< string > &files);
#if defined(WIN32)||defined(WIN64)||defined(WINCE)	
#else
		DLL_CLASS int ReadAllFileList(const char *basePath, list<string> &fileList);
#endif

	}
}

#endif OSUTIL_H_
