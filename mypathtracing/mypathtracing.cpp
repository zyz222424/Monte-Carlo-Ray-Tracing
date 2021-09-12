#include <iostream>
#include "SceneConfigLoader.h"
#include<direct.h>
#include<vector>
#include"Utils.h"
using namespace std;


int main(int argc, char* argv[]) {

	string objDirectory = "../data";
	vector<string> files = Utils::GetSubFolders(objDirectory);
	string objdir = Utils::SelectSubFolder(files);
	SceneConfigLoader::RenderSceneByConfig(objdir);
	return 0;
}