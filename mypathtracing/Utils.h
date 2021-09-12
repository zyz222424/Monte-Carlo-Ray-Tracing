#ifndef __UTILS_H__
#define __UTILS_H__
#include <iostream>
#include <io.h>
#include <vector>
#include <string>
#include <list>
using namespace std;
struct Utils
{
	static std::vector<std::string> GetSubFolders(const std::string& folder);
	static std::string SelectSubFolder(std::vector<std::string> &folders);
};

#endif