#include "Config.h"
#include <vector>
#include <set>
#include <glm/vec3.hpp>

class Vertex
{
public:
	Vertex(void);
	Vertex(glm::dvec3);
	Vertex(double, double, double);
	~Vertex(void);

	int id; // ������
	glm::dvec3 pos;
	std::set<int> neighbors;  // �ڽӵ�
	void addConnectVertex(int);  // ��ӱ��Ϊint���ڽӵ�
	void delConnectVertex(int);  // ɾ�����Ϊint���ڽӵ�
	bool isExistConnectVertex(int);  //�Ƿ��Ѿ�������ĳ���ڽӵ�
};