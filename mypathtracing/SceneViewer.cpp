#include "SceneViewer.h"
#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif
#ifdef __APPLE__
#include <gl/freeglut.h>
#else
#include <GL/freeglut.h>
#endif
#include <iostream>
#include <chrono>
#include <mutex>
#include <thread>

#include<time.h>
#include <fstream>
#include<Windows.h>
#include <sstream>
using namespace std;

namespace {
	int g_width, g_height;
	std::mutex g_write_color;
	std::vector<float> g_colors;
	vector<float> color;
	int i = 0;
}

PathTracer* SceneViewer::s_path_tracer = nullptr;

SceneViewer::SceneViewer(PathTracer* path_tracer, int width, int height) {
	s_path_tracer = path_tracer;
	g_width = width;
	g_height = height;
	// g_colors.resize(g_width * g_height * 3);
}

void SceneViewer::ViewScene() {  //������ʾ�Ĳ���
	clock_t startTime, endTime;
	//int temp_iterate = s_path_tracer->myiterate;
	startTime = clock();//��ʱ��ʼ
	std::thread render_thread([this]() {  //���߳̽�����Ⱦ
		while (i < s_path_tracer->myiterate){   //myiterate�ε���
			color = s_path_tracer->RenderScene(); //������Ⱦ  ���յõ���ɫ  ����vector�洢������
			g_write_color.lock();
			i++;
			g_write_color.unlock();
		}
		});

	while (true) {    //���̸߳�����ʾ������
		g_write_color.lock();
		if (i < s_path_tracer->myiterate){
			printf("\r��Ⱦ��[%.2lf%%]", i * 100.0 / (s_path_tracer->myiterate));
		}
		else{
			printf("\r��Ⱦ���[%.2lf%%]\n", i * 100.0 / (s_path_tracer->myiterate));

			// ����cout��������ָ��
			string ite;
			string depth;
			stringstream ss;
			ss << s_path_tracer->myiterate;
			ss >> ite;//���� res = ss.str();
			ss.clear();
			ss << s_path_tracer->m_max_depth;
			ss >> depth;
			char arr[255];
			SYSTEMTIME sys;
			GetLocalTime(&sys);

			sprintf_s(arr, "%d_%d_%d_%02d_%02d_%02d", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond);


			streambuf* coutBuf = cout.rdbuf();
			string objdir = s_path_tracer->m_result_directory + s_path_tracer->filename + '_' + "spp"+ ite
				+ '_' + "depth" + depth + '_' + "time"+string(arr)+".ppm";
			ofstream of(objdir);
			// ��ȡ�ļ�out.txt��������ָ��
			streambuf* fileBuf = of.rdbuf();
			cout.rdbuf(fileBuf);
			// ����cout��������ָ��Ϊout.txt����������ָ��

			cout << "P3\n" << g_width << " " << g_height << "\n255\n";
			for (int j = 0; j < g_height; j++) {
				for (int i = 0; i < g_width; i++) {
					int pixel_index = (j * g_width + i) * 3;
					clampfloat(color[pixel_index], 0, 1);
					clampfloat(color[pixel_index + 1], 0, 1);
					clampfloat(color[pixel_index + 2], 0, 1);
					int ir = int(255.99 * color[pixel_index]);
					int ig = int(255.99 * color[pixel_index + 1]);
					int ib = int(255.99 * color[pixel_index + 2]);
					cout << ir << " " << ig << " " << ib << "\n";
				}
			}

			of.flush();  //��of�������е��������
			of.close();  //�ر�of������

			// �ָ�coutԭ������������ָ��
			cout.rdbuf(coutBuf);

			endTime = clock();//��ʱ����
			cout << "The run time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
			g_write_color.unlock();
			break;
		}
		g_write_color.unlock();
		Sleep(100);
	}
	render_thread.join();
}