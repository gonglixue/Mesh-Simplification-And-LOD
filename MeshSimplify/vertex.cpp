#include "vertex.h"

Vertex::Vertex(void)
{
	id = -99;
	neighbors.clear();
}

Vertex::Vertex(glm::vec3 t)
{
	id = -98;
	neighbors.clear();
	pos = t;
}

Vertex::Vertex(double x, double y, double z)
{
	id = -97;
	neighbors.clear();
	pos = glm::vec3(x, y, z);
}

Vertex::~Vertex(void){}

void Vertex::addConnectVertex(int num)
{
	neighbors.insert(num);
}

void Vertex::delConnectVertex(int num) {
	neighbors.erase(num);
}

bool Vertex::isExistConnectVertex(int num)
{
	return (neighbors.count(num) > 0);
}