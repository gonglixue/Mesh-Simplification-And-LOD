#include "vertexGroup.h"
VertexGroup::VertexGroup(void)
{
	cntVertex = 0;
	isDeleted = new bool[Config::MAX_POINT_NUM];
	for (int i = 0; i < Config::MAX_POINT_NUM; i++)
	{
		isDeleted[i] = false;
	}
}

int VertexGroup::addVertex(Vertex p)
{
	cntVertex++;
	p.id = cntVertex;
	group[cntVertex] = p;
	return cntVertex;
}

void VertexGroup::delVertex(int _id)
{
	if (_id >= Config::MAX_POINT_NUM)
	{
		return;
	}
	isDeleted[_id] = true; // ��group��ɾ��

	// ���ڽӶ����neighbors��ɾ���Լ�
	for (set<int>::iterator it = group[_id].neighbors.begin(); it != group[_id].neighbors.end(); it++)
	{
		group[(*it)].delConnectVertex(_id);
	}
}

//u��v�Ĺ�ͬneighbor�ĸ���
int VertexGroup::getCommonVertexNum(int u, int v)
{
	int cnt = 0;
	for (set<int>::iterator it = group[u].neighbors.begin(); it != group[u].neighbors.end(); it++)
	{
		if (group[v].isExistConnectVertex(*it)) {
			cnt++;
		}
	}
	return cnt;
}
