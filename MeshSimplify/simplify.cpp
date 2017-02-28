#include "simplify.h"
Simplify::Simplify(void)
{
	eHeap = new EdgeHeap();
	vGroup = new VertexGroup();
	cntFace = 0;
}

Simplify::~Simplify(void)
{

}

void Simplify::start()
{
	for (int i = 0; i < cntDelFace; i += 2)
	{
		Edge e = eHeap->getMinDelta();
		Vertex* v1 = &(vGroup->group[e.v1]);
		Vertex* v2 = &(vGroup->group[e.v2]);
		Vertex v0 = e.v;
		int v0_id = vGroup->addVertex(v0);
		Vertex* pV0 = &(vGroup->group[v0_id]);  // 顶点收缩所产生新点的指针

		set<int> connectV;  //pV0的邻接点
		connectV.clear();
		eHeap->delEdge(e); // 删除边

		// 删除与v1相连的边，另一个端点添加的pV0的邻接点集合里,从另一个端点的邻接点集合里删除v1
		for (set<int>::iterator it = v1->neighbors.begin(); it != v1->neighbors.end(); it++)
		{
			if ((*it) != v2->id)
			{
				eHeap->delEdge(Edge((*it), v1->id));
				vGroup->group[(*it)].delConnectVertex(v1->id);
				connectV.insert((*it));
			}
		}

		for (set<int>::iterator it = v2->neighbors.begin(); it != v2->neighbors.end(); it++)
		{
			if ((*it) != v1->id)
			{
				eHeap->delEdge(Edge((*it), v2->id));
				vGroup->group[(*it)].delConnectVertex(v2->id);
				connectV.insert((*it));
			}
		}

		// 合并v1 v2的邻接点集合，成为新点v的邻接点集合
		for (set<int>::iterator it = connectV.begin(); it != connectV.end(); it++)
		{
			vGroup->group[(*it)].addConnectVertex(v0_id);  // 为新点添加邻接点
			vGroup->group[v0_id].addConnectVertex(*it);    // 反过来再添加一次邻接关系
		}

		// 删除v1,v2
		vGroup->isDeleted[v1->id] = true;
		vGroup->isDeleted[v2->id] = true;

		// 给新点加边
		for (set<int>::iterator it = connectV.begin(); it != connectV.end(); it++)
		{
			Edge e((*it), v0_id);
			calVAndDeltaV(e);  // 计算该边的v和delta

		}
	}
}

void Simplify::setRatio(double _ratio) {
	ratio = _ratio;
}

void Simplify::input()
{
	int cntv = 0, cntf = 0;
	char s[256];
	int tmp = 0;
	while (scanf("%s", s) == 1) {
		tmp++;
		switch (s[0]) {
		case '#': fgets(s, sizeof s, stdin); break;
		case 'v': {
			cntv++;
			double x, y, z;
			scanf("%lf %lf %lf", &x, &y, &z);
			vGroup->addVertex(Vertex(x, y, z));
			break;
		}
		case 'f': {
			cntf++;
			cntFace++;
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			//建立邻接关系,已检查
			vGroup->group[a].addConnectVertex(b);
			vGroup->group[a].addConnectVertex(c);
			vGroup->group[b].addConnectVertex(a);
			vGroup->group[b].addConnectVertex(c);
			vGroup->group[c].addConnectVertex(a);
			vGroup->group[c].addConnectVertex(b);
			break;
		}
		default: break;
		}
	}

	// 将边加入到堆中
	for (int i = 1; i <= vGroup->cntVertex; i++) {
		for (set<int>::iterator it = vGroup->group[i].neighbors.begin(); it != vGroup->group[i].neighbors.end(); it++)
		{
			//if (i < (*it))
				//break;
			Edge e((*it), i);
			calVAndDeltaV(e);  // 每创建一条边，为其计算收缩后的点和error
			eHeap->addEdge(e);
		}
	}
	cntDelFace = (int)((1 - ratio)*cntFace);//计算应该剩下多少面
}

void Simplify::output()
{
	int cnt = 0;
	int cntv = 0, cntf = 0;
	for (int i = 1; i <= vGroup->cntVertex; i++)
	{
		if (vGroup->isDeleted[i])
			continue;
		Vertex* v = &vGroup->group[i];
		cnt++;
		v->id = cnt;
		printf("v %lf %lf %lf\n", v->pos.x, v->pos.y, v->pos.z);
	}
	for (int i = 1; i <= vGroup->cntVertex; i++)
	{
		if (vGroup->isDeleted[i])
			continue;
		Vertex* v = &(vGroup->group[i]);
		for (set<int>::iterator it1 = v->neighbors.begin(); it1 != v->neighbors.end(); it1++)
		{
			if(i > (*it1))
				continue;
			for (set<int>::iterator it2 = v->neighbors.begin(); it2 != v->neighbors.end(); it2++)
			{
				if ((*it1) < (*it2) && (vGroup->group[(*it1)].isExistConnectVertex(*it2)))
				{
					printf("f %d %d %d\n", v->id, vGroup->group[(*it1)].id, vGroup->group[(*it2)].id);
					cntf++;
				}
			}
		}
	}
}