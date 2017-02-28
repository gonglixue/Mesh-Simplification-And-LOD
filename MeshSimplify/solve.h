#pragma once
//#include <glm/vec4.hpp>
//#include <glm/matrix.hpp>
//#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include "Config.h"
#include <cmath>
// 求解论文中的公式(1)
class Solve
{
public:
	Solve(glm::mat4& _m, glm::vec4& _v);
	~Solve(void);
	glm::vec4 getAns();
	glm::mat4 m;
	glm::vec4 v;

};