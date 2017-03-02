#pragma once
#include "edgeHeap.h"
#include "vertexGroup.h"
#include "solve.h"
#include <string>
#include <fstream>

using namespace std;

class Simplify
{
	double ratio;
	int cntFace, cntDelFace;
	EdgeHeap* eHeap;
	VertexGroup* vGroup;
public:
	Simplify(void);
	~Simplify(void);

	void setRatio(double);
	void setLeftFaceNum(int);

	void input();
	void input(string inFile);
	void start();
	void output();

	glm::mat4 calVertexDelta(int);
	glm::vec3 calVertexPos(Edge&, glm::mat4); // 根据一个遍两个点的误差矩阵计算收缩后的点位置

	void calVAndDeltaV(Edge&);  //计算并确定一个边的v和deltaV;
};
