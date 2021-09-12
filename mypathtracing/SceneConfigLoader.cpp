#include "Scene.h"
#include "PathTracer.h"
#include "SceneViewer.h"
//#include "LuaConfigParser.h"
#include "SceneConfigLoader.h"
#include <iostream>
#include <cassert>

#include"Parser.h"
using namespace std;

void SceneConfigLoader::RenderSceneByConfig(std::string config_file) {

	Parser parser;
	parser.parse(config_file);

	parser.print();
	int width = parser.resultwidth, height = parser.resultheight;  //设置宽高
	float fov_y = parser.resultfov;    //相机在x轴的观察角度
	float fov_x = fov_y * width / height;
	Model model(parser.objfilename);      //初始化模型  模型对象中有模型需要的所有信息

	Vec3f center=parser.lookat;// = model.m_bbox.Center();             //中心	
	//center += parser.lookat;
	Vec3f eye = parser.lookfrom;    //眼睛的位置
	Vec3f up = parser.cameraupdirection;

	Scene scene(width, height);                       //初始化场景
	scene.AddModel(&model);       //总共一个模型                    //场景中加入模型
	scene.InitializeKdTree();     //scene是单个节点的kdtree                    //初始化KdTree
	float aperture = parser.aperture;
	float focusdist = parser.focusdist;
	scene.SetViewPoint(eye, center, up, fov_x, aperture,focusdist);  //设置视角

	scene.m_ambient = parser.sceneambient;  //环境光

	//int external_light_num = parser.externallightillumination;    //外部光数量   这个cornellbox模型中，外部光为0
	//for (int i = 0; i < external_light_num; ++i) {   //对外部光进行遍历
	//    vec3 origin = parser.GetVec3f("el_origin_" + std::to_string(i));
	//    vec3 dx = parser.GetVec3f("el_dx_" + std::to_string(i));
	//    vec3 dy = parser.GetVec3f("el_dy_" + std::to_string(i));
	//    vec3 emission = parser.GetVec3f("el_emission_" + std::to_string(i));
	//    scene.m_lights.emplace_back(ExternalLight(origin, dx, dy, emission));
	//}

	PathTracer path_tracer(&scene);   //加入场景
	path_tracer.m_max_depth = parser.maxiterationdepthforray;   //光线递归的最大深度

	path_tracer.m_result_directory = parser.resultdir;  //存储图片的目录
	path_tracer.myiterate = parser.myiterate;
	path_tracer.filename= parser.filename;
	SceneViewer display(&path_tracer, width, height);  //进行显示
	display.ViewScene();  //输入是否进行显示和存储图片 进行显示
}