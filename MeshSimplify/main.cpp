#include <iostream>
#include <time.h>
#include "Simplify.h"
#include "Config.h"
#include "solve.h"


#include "shader.h"
#include "camera.h"
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <SOIL.h>
#include <GLFW\glfw3.h>
using namespace std;

// 窗口属性
GLuint screenWidth = 800;
GLuint screenHeight = 600;
// 函数原型
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_btn_callback(GLFWwindow* window, int button, int action, int mods);
void Do_Movement();
// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;
bool CameraRotate = false;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

GLFWwindow* window;

void glfwSetting()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	window = glfwCreateWindow(screenWidth, screenHeight, "mesh simplification", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// callback
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_btn_callback);
}
void glewSetting()
{
	glewExperimental = GL_TRUE;
	glewInit();

	glViewport(0, 0, screenWidth, screenHeight);
	glEnable(GL_DEPTH_TEST);
}
/*
argv[1]: input.obj
argv[2]: output.obj
argv[3]: simplification ratio
*/

int main(int argc, char* argv[])
{
	printf("begin");
	if (argc != 4) {
		cout << "error input" << endl;
		return -1;
	}
	else {

		glfwSetting();
		glewSetting();

		// setup and compile our shaders
		Shader ourShader("./shader.vs", "./shader.frag");
		GLuint VBO, VAO, EBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		clock_t start = clock();
		printf("new simplify");
		Simplify* meshSimplify = new Simplify();
		freopen(argv[1], "r", stdin);
		freopen(argv[2], "w", stdout);
		meshSimplify->setRatio(atof(argv[3]));  // 简化率
		//printf("input\n");
		meshSimplify->input();  // 读入
		//printf("开始简化");
		meshSimplify->start();  // 开始简化
		//printf("简化完毕，开始写入");
		//meshSimplify->output();  // 输出文件

		clock_t finish = clock();
		cout << "# time use: " << (double)(finish - start) / CLOCKS_PER_SEC << "s" << endl;
	}

	return 0;
}