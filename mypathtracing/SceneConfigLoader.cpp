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
	int width = parser.resultwidth, height = parser.resultheight;  //���ÿ��
	float fov_y = parser.resultfov;    //�����x��Ĺ۲�Ƕ�
	float fov_x = fov_y * width / height;
	Model model(parser.objfilename);      //��ʼ��ģ��  ģ�Ͷ�������ģ����Ҫ��������Ϣ

	Vec3f center=parser.lookat;// = model.m_bbox.Center();             //����	
	//center += parser.lookat;
	Vec3f eye = parser.lookfrom;    //�۾���λ��
	Vec3f up = parser.cameraupdirection;

	Scene scene(width, height);                       //��ʼ������
	scene.AddModel(&model);       //�ܹ�һ��ģ��                    //�����м���ģ��
	scene.InitializeKdTree();     //scene�ǵ����ڵ��kdtree                    //��ʼ��KdTree
	float aperture = parser.aperture;
	float focusdist = parser.focusdist;
	scene.SetViewPoint(eye, center, up, fov_x, aperture,focusdist);  //�����ӽ�

	scene.m_ambient = parser.sceneambient;  //������

	//int external_light_num = parser.externallightillumination;    //�ⲿ������   ���cornellboxģ���У��ⲿ��Ϊ0
	//for (int i = 0; i < external_light_num; ++i) {   //���ⲿ����б���
	//    vec3 origin = parser.GetVec3f("el_origin_" + std::to_string(i));
	//    vec3 dx = parser.GetVec3f("el_dx_" + std::to_string(i));
	//    vec3 dy = parser.GetVec3f("el_dy_" + std::to_string(i));
	//    vec3 emission = parser.GetVec3f("el_emission_" + std::to_string(i));
	//    scene.m_lights.emplace_back(ExternalLight(origin, dx, dy, emission));
	//}

	PathTracer path_tracer(&scene);   //���볡��
	path_tracer.m_max_depth = parser.maxiterationdepthforray;   //���ߵݹ��������

	path_tracer.m_result_directory = parser.resultdir;  //�洢ͼƬ��Ŀ¼
	path_tracer.myiterate = parser.myiterate;
	path_tracer.filename= parser.filename;
	SceneViewer display(&path_tracer, width, height);  //������ʾ
	display.ViewScene();  //�����Ƿ������ʾ�ʹ洢ͼƬ ������ʾ
}