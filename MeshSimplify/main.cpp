#include <iostream>
#include <time.h>
#include "Simplify.h"
#include "Config.h"
#include "solve.h"

//#include <GLFW\glfw3.h>
#include "shader.h"
#include "camera.h"
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <SOIL.h>

using namespace std;

// ��������
GLuint screenWidth = 800;
GLuint screenHeight = 600;
// ����ԭ��
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void mouse_btn_callback(GLFWwindow* window, int button, int action, int mods);
//void Do_Movement();
// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;
bool CameraRotate = false;

int main(int argc, char* argv[])
{
	printf("begin");
	if (argc != 4) {
		cout << "error input" << endl;
		return -1;
	}
	else {
		clock_t start = clock();
		printf("new simplify");
		Simplify* meshSimplify = new Simplify();
		freopen(argv[1], "r", stdin);
		freopen(argv[2], "w", stdout);
		meshSimplify->setRatio(atof(argv[3]));  // ����
		//printf("input\n");
		meshSimplify->input();  // ����
		//printf("��ʼ��");
		meshSimplify->start();  // ��ʼ��
		//printf("����ϣ���ʼд��");
		meshSimplify->output();  // ����ļ�

		clock_t finish = clock();
		cout << "# time use: " << (double)(finish - start) / CLOCKS_PER_SEC << "s" << endl;
	}

	return 0;
}