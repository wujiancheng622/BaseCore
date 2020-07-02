#include <stdio.h>   
#include <stdlib.h>  
#include <string.h>


#if defined(WIN32)||defined(WIN64)||defined(WINCE)	
#include <direct.h>
#include <io.h>
#else
#include <dirent.h>
#include <unistd.h>
#endif
#include "OSUtil.h"
using namespace std;


namespace BaseCore
{
	namespace Common
	{

#if defined(WIN32)||defined(WIN64)||defined(WINCE)	

		int ReadDirList(const char *basePath, list<string> &dirs)
		{
			string tmp = basePath;
			tmp += +"/*";
			_finddata_t file;
			long lf;
			//输入文件夹路径
			if ((lf = _findfirst(tmp.c_str(), &file)) == -1)
			{
				printf("\n dir:%s not found!!!  \n", tmp.c_str());
				return -1;
			}
			else
			{
				while (_findnext(lf, &file) == 0)
				{
					if (strcmp(file.name, ".") == 0 || strcmp(file.name, "..") == 0)
						continue;
					else if (file.attrib == 16)//文件夹
					{
						string fullDirName = basePath;
						fullDirName += "/";
						fullDirName += file.name;
						dirs.push_back(fullDirName);
					}
				}
			}
			_findclose(lf);
			return 0;
		}

		int ReadFileList(const char *basePath, list< string > &files)
		{
			string tmp = basePath;
			tmp += +"/*";

			_finddata_t file;
			long lf;
			//输入文件夹路径
			if ((lf = _findfirst(tmp.c_str(), &file)) == -1)
			{
				printf("\n dir:%s not found!!!  \n", tmp.c_str());
				return -1;
			}
			else
			{
				while (_findnext(lf, &file) == 0)
				{
					if (strcmp(file.name, ".") == 0 || strcmp(file.name, "..") == 0)
						continue;
					if (file.attrib == 32)//文件
					{
						string fullFileName = basePath;
						fullFileName += "/";
						fullFileName += file.name;
						files.push_back(fullFileName);
					}
				}
			}
			_findclose(lf);
			return 0;
		}
#else
		int ReadFileList(const char *basePath, list< string > &fileList)
		{
			DIR *dir;
			struct dirent *ptr;
			char base[1000];
			if ((dir = opendir(basePath)) == NULL)
			{
				perror("Open dir error... ");
				return -1;
			}
			while ((ptr = readdir(dir)) != NULL)
			{
				if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)    ///current dir OR parrent dir
					continue;
				else if (ptr->d_type == 8)    ///file
				{
					char fileName[512] = { 0 };
					sprintf(fileName, "%s/%s", basePath, ptr->d_name);
					fileList.push_back(fileName);
				}

			}
			closedir(dir);
			return 0;
		}
		int ReadDirList(const char *basePath, list<string> &dirList)
		{
			DIR *dir;
			struct dirent *ptr;
			char base[1000];

			if ((dir = opendir(basePath)) == NULL)
			{
				perror("Open dir error... ");
				return -1;
			}
			while ((ptr = readdir(dir)) != NULL)
			{
				if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)    ///current dir OR parrent dir
					continue;
				if (ptr->d_type == 4)    ///dir
				{
					char dirName[512] = { 0 };
					sprintf(dirName, "%s/%s", basePath, ptr->d_name);
					dirList.push_back(dirName);
				}
			}
			closedir(dir);
			return 0;
		}
		int ReadAllFileList(const char *basePath, list<string> &fileList)
		{
			DIR *dir;
			struct dirent *ptr;
			char base[1000];

			if ((dir = opendir(basePath)) == NULL)
			{
				perror("Open dir error... ");
				return -1;
			}
			while ((ptr = readdir(dir)) != NULL)
			{
				if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)    ///current dir OR parrent dir
					continue;
				else if (ptr->d_type == 8)    ///file
				{
					char fileName[512] = { 0 };
					sprintf(fileName, "%s/%s", basePath, ptr->d_name);
					fileList.push_back(fileName);
				}
				else if (ptr->d_type == 4)    ///dir
				{
					memset(base, '\0', sizeof(base));
					strcpy(base, basePath);
					strcat(base, "/");
					strcat(base, ptr->d_name);
					ReadAllFileList(base, fileList);
				}
			}
			closedir(dir);
			return 0;
		}
#endif

	}
}
