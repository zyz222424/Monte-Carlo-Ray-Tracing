#pragma once
#include <string>
#include "Parser.h"
#include<iostream>
#include <fstream>
#include <string>
#include"Types.h"
using namespace std;

class Parser
{
public:
	bool parse(std::string folder);
	void print();
	string filename;
	string objfilename;
	string resultdir;


	Vec3f lookat;
	Vec3f lookfrom;
	Vec3f cameraupdirection;
	Vec3f sceneambient;

	int resultwidth;
	int resultheight;
	int resultfov;  //ºÍyµÄ¼Ð½Ç
	float focusdist;
	float aperture;
	int maxiterationdepthforray;
	int myiterate;
	int externallightillumination;

};

