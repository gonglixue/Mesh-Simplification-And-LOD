#pragma once
#include <vector>
#include "vertex.h"
#include "Config.h"
using namespace std;

class VertexGroup
{
public:
	VertexGroup(void);
	~VertexGroup(void);
	Vertex group[Config::MAX_POINT_NUM];
	int cntVertex;
	bool* isDeleted;
	int addVertex(Vertex); // �����¼���Ľ��id
	void delVertex(int);   // ��group��ɾ��id����
	int getCommonVertexNum(int, int);
};