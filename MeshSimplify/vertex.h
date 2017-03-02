#include "Config.h"
#include <vector>
#include <set>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>

class Vertex
{
public:
	Vertex(void);
	Vertex(glm::vec3);
	Vertex(double, double, double);
	~Vertex(void);

	int id; // ������
	glm::vec3 pos;
	//glm::mat4 matQ;
	std::set<int> neighbors;  // �ڽӵ�
	void addConnectVertex(int);  // ��ӱ��Ϊint���ڽӵ�
	void delConnectVertex(int);  // ɾ�����Ϊint���ڽӵ�
	bool isExistConnectVertex(int);  //�Ƿ��Ѿ�������ĳ���ڽӵ�
};