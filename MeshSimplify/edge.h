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
	int id;  // 边序号
	int v1, v2;  // 端点编号
	glm::dvec3 v;  // 收缩后形成点
	double deltaV;  //边收缩成点v的代价
};