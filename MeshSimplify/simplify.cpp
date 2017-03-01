#include "simplify.h"
Simplify::Simplify(void)
{
	eHeap = new EdgeHeap();
	vGroup = new VertexGroup();
	cntFace = 0;
	printf("finish construct simplify");
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
		Vertex* pV0 = &(vGroup->group[v0_id]);  // ���������������µ��ָ��

		set<int> connectV;  //pV0���ڽӵ�
		connectV.clear();
		eHeap->delEdge(e); // ɾ����

		// ɾ����v1�����ıߣ���һ���˵���ӵ�pV0���ڽӵ㼯����,����һ���˵���ڽӵ㼯����ɾ��v1
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

		// �ϲ�v1 v2���ڽӵ㼯�ϣ���Ϊ�µ�v���ڽӵ㼯��
		for (set<int>::iterator it = connectV.begin(); it != connectV.end(); it++)
		{
			vGroup->group[(*it)].addConnectVertex(v0_id);  // Ϊ�µ�����ڽӵ�
			vGroup->group[v0_id].addConnectVertex(*it);    // �����������һ���ڽӹ�ϵ
		}

		// ɾ��v1,v2
		vGroup->isDeleted[v1->id] = true;
		vGroup->isDeleted[v2->id] = true;
		//printf("# del %d %d vertex\n", v1->id, v2->id);
		// ���µ�ӱ�
		for (set<int>::iterator it = connectV.begin(); it != connectV.end(); it++)
		{
			Edge e((*it), v0_id);
			calVAndDeltaV(e);  // ����ñߵ�v��delta
			eHeap->addEdge(e);
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
			//�����ڽӹ�ϵ,�Ѽ��
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

	// ���߼��뵽����
	for (int i = 1; i <= vGroup->cntVertex; i++) {
		for (set<int>::iterator it = vGroup->group[i].neighbors.begin(); it != vGroup->group[i].neighbors.end(); it++)
		{
			if (i < (*it))
				break;
			Edge e((*it), i);
			calVAndDeltaV(e);  // ÿ����һ���ߣ�Ϊ�����������ĵ��error
			eHeap->addEdge(e);
		}
	}
	cntDelFace = (int)((1.0 - ratio)*cntFace);//����Ӧ��ʣ�¶�����
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
			if (i >= (*it1))
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

void Simplify::calVAndDeltaV(Edge& e) {
	glm::mat4 mat = calVertexDelta(e.v1) + calVertexDelta(e.v2);
	e.v = calVertexPos(e, mat);  //�����e������Ĳ������µ������
	glm::vec4 X(e.v.x, e.v.y, e.v.z, 1.0f);  // column vector
	if (vGroup->getCommonVertexNum(e.v1, e.v2) != 2)
	{
		e.deltaV = 0;
		return;
	}
	// ����vT(Qv)
	glm::vec4 temp = mat*X;
	double pri = glm::dot(X, temp);
	e.deltaV = pri;
	//printf("# edge %d error %f\n", e.id, e.deltaV);
}
// Q��Ҫÿ�������������𣿣�
glm::mat4 Simplify::calVertexDelta(int _id)
{
	glm::mat4 Q(0.0);  // Ĭ��Ϊ��λ�����ʼ��Ϊ0
	Vertex* p = &(vGroup->group[_id]);
	for (set<int>::iterator it1 = p->neighbors.begin(); it1 != p->neighbors.end(); it1++) {
		for (set<int>::iterator it2 = p->neighbors.begin(); it2 != p->neighbors.end(); it2++)
		{
			if ((*it1) < (*it2) && (vGroup->group[*it1].isExistConnectVertex(*it2)))
			{
				Vertex* v1 = &(vGroup->group[(*it1)]);
				Vertex* v2 = &(vGroup->group[(*it2)]);
				// p v1 v2����һ��face, ƽ�淽��ax+by+cz+d=0
				// ��face�ķ�����(a,b,c)
				glm::vec3 t1 = v1->pos - p->pos;
				glm::vec3 t2 = v2->pos - p->pos;
				glm::vec3 normal = glm::normalize(glm::cross(t1, t2));
				// ��d
				double d = -(glm::dot(normal, p->pos));
				glm::vec4 P = glm::vec4(normal, d);
				// K = ppT
				glm::mat4 K = glm::outerProduct(P, P);
				// ���
				Q += K;
			}
		}
	}
	return Q;
}

// ����������������µ������
glm::vec3 Simplify::calVertexPos(Edge& e, glm::mat4 m)
{
	glm::vec3 mid = (vGroup->group[e.v1].pos + vGroup->group[e.v2].pos) / 2.0f;  //�е㣬Ӧ���˻������
	// ���þ������һ��Ϊ 0 0 0 1
	// opengl ����Ĭ������Ϊ��mat[col][row]
	m[0][3] = 0;
	m[1][3] = 0;
	m[2][3] = 0;
	m[3][3] = 1;

	glm::vec4 Y = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	Solve* solve = new Solve(m, Y);
	glm::vec4 ans = solve->getAns();
	if (ans.w > Config::EPS) {
		//printf("# new v(%f,%f,%f)\n", ans.x, ans.y, ans.z);
		return glm::vec3(ans.x, ans.y, ans.z);
	}
		
	else
	{
		//printf("# new v(%f,%f,%f)\n", mid.x, mid.y, mid.z);
		return mid;
	}
		

}