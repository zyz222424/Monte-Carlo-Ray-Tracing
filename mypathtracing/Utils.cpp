#include "Utils.h"
#include "windows.h"
using namespace std;
std::vector<std::string> Utils::GetSubFolders(const std::string& folder)
{
	std::string path = folder+"\\*.*";
	std::vector<std::string> files;
	struct _finddata_t file_info;

	intptr_t  file_handler = _findfirst(path.c_str(), &file_info);

	while (file_handler != -1)
	{
		if ((file_info.attrib & _A_SUBDIR)&&!(strcmp(file_info.name,".")==0||strcmp(file_info.name,"..")==0)) 
			files.push_back(file_info.name);
		if (_findnext(file_handler, &file_info) != 0) break;
	}
	_findclose(file_handler);

	return files;
}



std::string Utils::SelectSubFolder(std::vector<std::string>& folders)
{
	if (folders.size())
	{
		for (int i = 0, len = folders.size(); i < len; ++i)
		{
			cout << i << ":" << folders[i] << endl;
		}

		int id;
		while (true)
		{
			cout << "please choose one scene to render: ";
			cin >> id;
			if (id >= 0 && id < folders.size()) break;
			else cout << "valid input" << endl;
		}


		return folders[id];
	}
}



