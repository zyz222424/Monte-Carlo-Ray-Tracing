#include "Scene.h"
#include <iostream>
#include <cassert>
#include<iostream>
using namespace std;

namespace {
const float PI = 3.1415926f;
}

Scene::Scene(int width, int height) : m_width(width), m_height(height) {
    m_colors.resize(3 * m_width * m_height);  //��ʼ��m_colors����Ϊ3 * m_width * m_height
    m_colors.assign(m_colors.size(), 0);  //��ʼ��m_colorsΪ0
}

Scene::~Scene() {
}

void Scene::SetViewPoint(const Vec3f &eye, const Vec3f &center, const Vec3f &up,
                         float fov_x,float aperture,float focusdist) {

	lens_radius = aperture / 2;
	//cout << lens_radius << endl;
    m_eye = eye;
    m_direction = (center - eye).normalized();
    m_right = (m_direction.cross(up)).normalized();
    //m_up = (m_right.cross(m_direction)).normalized();
	m_up = up.normalized();
    m_fov_x = fov_x;      //�ǵ���ʦ��ʱ������fov_y�ǵøĳ�fov_y
    m_view_x = m_right* 2 * tanf(m_fov_x * PI / 360) * focusdist;
    m_view_y = m_up * 2 * tanf(m_fov_x * (float(m_height) / m_width) * PI / 360) * focusdist;
    m_view_z = m_direction * focusdist;
	lower_left_corner = m_eye - m_view_x/2 - m_view_y/2 + m_view_z;
	//cout << m_view_x << m_view_y << m_view_z << lower_left_corner << endl;
}

Vec3f Scene::random_in_unit_disk()
{
	Vec3f p;
	do {
		p = 2.0 * Vec3f(Rand01(), Rand01(), 0) - Vec3f(1, 1, 0);
	} while (p.dot(p) >= 1.0);
	return p;
}

void Scene::AddModel(AbstractObject *model) {
    m_scene_models.emplace_back(model);
}

void Scene::InitializeKdTree() {
    m_kd_tree.BuildTree(m_scene_models);
}

bool Scene::IntersectScene(Ray &ray, Intersection &intersection) {
    return m_kd_tree.Hit(ray, intersection);
}

Ray Scene::GetRay(int x, int y) {
	Vec3f rd = lens_radius * random_in_unit_disk();
	Vec3f offset = m_right * rd.x() + m_up * rd.y();//�����Ǿ���
	float u = float(x + Rand01()) / float(m_width);  //������Ϊ�˷�����
	float v = float(y + Rand01()) / float(m_height);

    return Ray(m_eye+offset, lower_left_corner + u * m_view_x + v * m_view_y - m_eye - offset);
}
