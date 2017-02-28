#include "solve.h"

Solve::Solve(glm::mat4& _m, glm::vec4& _v)
{
	m = _m;
	v = _v;
}

Solve::~Solve(void) {}

glm::vec4 Solve::getAns()
{
	glm::vec4 X;
	glm::mat4 inverseM = glm::inverse(m);
	X = inverseM * v;
	return X;
}