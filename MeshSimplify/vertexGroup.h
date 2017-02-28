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
	int addVertex(Vertex); // 返回新加入的结点id
	void delVertex(int);   // 在group中删除id顶点
	int getCommonVertexNum(int, int);
};