#ifndef INPUT_H_
#define INPUT_H_

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

bool keys[1024];
glm::vec4 mouse;
glm::vec2 scroll;
double prevX, prevY;
bool firstMouse = true;
bool mouseLeft = false;
bool mouseRight = false;
bool mouseToggle = false;

void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}
void mouseCallback(GLFWwindow* window, double x, double y) {
	if (firstMouse) {
		prevX = x;
		prevY = y;
		mouse.z = 0.0;
		mouse.w = 0.0;
		firstMouse = false;
	}

	mouse = glm::vec4(x, y, mouse.z + (x - prevX), mouse.q + (prevY - y));//default inverted y axis
	prevX = x;
	prevY = y;
}
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	scroll.x += xoffset;
	if (scroll.y >= 1.0f && scroll.y <= 90.0f)
		scroll.y -= yoffset;
	if (scroll.y <= 1.0f)
		scroll.y = 1.0f;
	if (scroll.y >= 90.0f)
		scroll.y = 90.0f;
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		mouseLeft = true;
		mouseToggle = true;
	}
	else {
		mouseLeft = false;
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		mouseRight = true;
		mouseToggle = false;
	}
	else {
		mouseRight = false;
	}
}

bool getKey(int key) { return keys[key]; }
glm::vec4 getMouse() { return mouse; }
glm::vec2 getScroll() { return scroll; }
bool isMouseLeftDown() { return mouseLeft; }
bool isMouseRightDown() { return mouseRight; }
bool getMouseToggle() { return mouseToggle; }

void initInput(GLFWwindow* window) {
	glfwSetKeyCallback(window, keyboardCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetScrollCallback(window, scrollCallback);
}

#endif //Input.h
