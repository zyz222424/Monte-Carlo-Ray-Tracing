
#include "Parser.h"

bool Parser::parse(std::string folder)
{
	string objfile = "../data/" + folder + "/" + folder + ".scene";
	ifstream file(objfile);
	//cout << objfile << endl;
	string type;
	if (!file.is_open())
	{
		cout << "opening scene file failed!!! Exit" << endl;
		return false;
	}
	else
	{
		while (file >> type)
		{
			if (type == "obj")
			{
				file >> objfilename;
				filename = objfilename.substr(0, objfilename.find('.'));
				//cout << "filename" << "...." << filename << endl;
				objfilename = "../data/" + folder + "/" + objfilename;
			}
			else if (type == "resultdir")
			{
				file >> resultdir;
				resultdir = "../" + resultdir+"/";
			}
			else if (type == "resultwidth")
			{
				file >> resultwidth;
			}
			else if (type == "resultheight")
			{
				file >> resultheight;
			}
			else if (type == "resultfov")
			{
				file >> resultfov;
			}
			else if (type == "lookat")
			{
				file >> lookat[0]>> lookat[1] >> lookat[2];
			}
			else if (type == "lookfrom")
			{
				file >> lookfrom[0]>> lookfrom[1]>> lookfrom[2];
			}
			else if (type == "cameraupdirection")
			{
				file >> cameraupdirection[0]>> cameraupdirection[1]>> cameraupdirection[2];
			}
			else if (type == "focusdist")
			{
				file >> focusdist;
				if (focusdist == 0)
					focusdist = (lookfrom-lookat).norm();  //距离 lookfrom和lookat之间的距离
			}
			else if (type == "aperture")
			{
				file >> aperture;
			}
			else if (type == "maxiterationdepthforray")
			{
				file >> maxiterationdepthforray;
			}
			else if (type == "myiterate")
			{
				file >> myiterate;
			}
			else if (type == "sceneambient")
			{
				file >> sceneambient[0]>> sceneambient[1]>> sceneambient[2];
			}
			else if (type == "externallightillumination")
			{
				file >> externallightillumination;
			}
		}

		file.close();


		return true;
	}

}

void Parser::print()
{
	cout <<endl<< "CONFIGURE:" <<endl<< endl;
	cout <<"objfilename    "<< objfilename << endl;
	cout << "resultdir    " << resultdir << endl;
	cout << "lookat    " << lookat[0] <<' '<< lookat[1] << ' ' << lookat[2]<< endl;
	cout << "lookfrom    " << lookfrom[0] <<' '<< lookfrom[1]<<' '<< lookfrom[2]<< endl;
	cout << "cameraupdirection    " << cameraupdirection[0]<<' '<< cameraupdirection[1] <<' '<< cameraupdirection[2] << endl;
	cout << "focusdist    " << focusdist<<endl;
	cout << "aperture    " << aperture<<endl;
	cout << "sceneambient    " << sceneambient[0] << ' ' << sceneambient[1] << ' ' << sceneambient[2] << endl;
	cout << "resultwidth     " << resultwidth << endl;
	cout << "resultheight    " << resultheight << endl;
	cout << "resultfov    " << resultfov << endl;
	cout << "maxiterationdepthforray    " << maxiterationdepthforray << endl;
	cout << "externallightillumination    " << externallightillumination << endl << endl;
}
