#include "edgeHeap.h"

EdgeHeap::EdgeHeap(void)
{
	cntEdge = 0;
	// ?
	for (int i = 0; i < Config::MAX_EDGE_NUM; i++)
	{
		isDeleted[i] = false;
	}
}

EdgeHeap::~EdgeHeap(void)
{

}

void EdgeHeap::addEdge(Edge& e)
{
	cntEdge++;
	e.id = cntEdge;  // id 从1开始?
	int u = min(e.v1, e.v2);
	int v = max(e.v1, e.v2);
	mapEdgeToID[make_pair(u, v)] = cntEdge;  //将该顶点对映射到id为cntEdge的边
	pq.push(e);
}

Edge EdgeHeap::getMinDelta() {
	if (pq.size() <= 0) {
		return Edge(0, 0);
	}
	while (isDeleted[pq.top().id]) {
		pq.pop();
	}
	// 找到第一个有效顶点（未被删除的顶点）
	Edge e = pq.top();
	pq.pop();
	return e;
}

void EdgeHeap::delEdge(Edge e)
{
	int u = min(e.v1, e.v2);
	int v = max(e.v1, e.v2);
	int ID = mapEdgeToID[make_pair(u, v)];
	isDeleted[ID] = true;  // 删除
}
