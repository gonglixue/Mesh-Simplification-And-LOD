#pragma once
#include <glm\vec3.hpp>
#include <cstdlib>
#include <cstdio>
#include "Config.h"

class Edge
{
public:
	Edge(int _u = -99, int _v = -99);
	~Edge(void);
	int id;  // �����
	int v1, v2;  // �˵���
	glm::dvec3 v;  // �������γɵ�
	double deltaV;  //�������ɵ�v�Ĵ���
};