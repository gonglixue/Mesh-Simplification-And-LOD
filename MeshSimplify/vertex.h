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

	int id; // 顶点编号
	glm::vec3 pos;
	//glm::mat4 matQ;
	std::set<int> neighbors;  // 邻接点
	void addConnectVertex(int);  // 添加编号为int的邻接点
	void delConnectVertex(int);  // 删除编号为int的邻接点
	bool isExistConnectVertex(int);  //是否已经存在了某个邻接点
};