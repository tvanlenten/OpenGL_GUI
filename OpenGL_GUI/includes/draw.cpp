#include "OpenGL\OpenGL.h"
#include <iostream>

//#define width 1280
//#define height 720

#define width 1920
#define height 1080

int main() {
	Control control(width, height, "OpenGL Example", true);
	Camera camera(width, height, glm::vec3(-2.0f, 1.0f, -2.0f), 90.0f, 0.1f, 100.0f, 0.1f, 0.1f);
	FrameBuffer screen(width, height);

	//Texture tex("textures/t1.jpg", GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, true);
	Shader shader("shaders/vertex.vert", "shaders/frag.frag", nullptr, false);

	Mesh cube;
	cube.createCube();


	GUI gui(width, height, 0.1, 0.04, glm::vec3(0.05), 0.9);

	char txtA[64], txtB[64], txtC[64];
	int s;

	s = snprintf(txtA, 64, "Simple GUI");
	gui.addText(txtA, 0.08, CENTER_SIDE, glm::vec3(1.0), glm::vec3(0.239, 0.431, 0.580));

	s = snprintf(txtB, 64, "text B");
	gui.addText(txtB, 0.05, RIGHT_SIDE, glm::vec3(1.0));

	s = snprintf(txtC, 64, "text C");
	gui.addText(txtC, 0.05, LEFT_SIDE, glm::vec3(1.0));

	char sliderA[64] = "slider val: %f";
	double aVal = 0.3;
	gui.addSlider(sliderA, 0.05, &aVal, -3.0, 100.0, LEFT_SIDE, glm::vec3(1.0), glm::vec3(0.0,1.0,0.0));

	char buttonA[64] = "Button A";
	double buttonVal0 = 0.0;
	gui.addButton(buttonA, 0.05, &buttonVal0, CENTER_SIDE, glm::vec3(1.0), glm::vec3(0.0,0.0,1.0));

	char buttonB[64] = "Button B";
	double buttonVal1 = 0.0;
	gui.addButton(buttonB, 0.05, &buttonVal1, CENTER_SIDE, glm::vec3(1.0), glm::vec3(0.0, 1.0, 0.0));

	char buttonC[64] = "Button C";
	double buttonVal2 = 0.0;
	gui.addButton(buttonC, 0.05, &buttonVal2, CENTER_SIDE, glm::vec3(1.0), glm::vec3(1.0, 0.0, 0.0));

	
	control.depthTest(true);
	control.cull(GL_FRONT);
	//control.wireframe(true);
	control.showMouse(true);
	while (!control.shouldQuit()) {
		control.update();
		camera.update();
		gui.update(glm::vec2(0.4,0.4), glm::vec2(getMouse().x / double(width), getMouse().y / double(height)), isMouseLeftDown());

		screen.use();
		screen.clear();

		control.transparency(false);
		control.depthTest(true);
		shader.use();
		shader.setFloat("time", control.getTime());
		shader.setMat4("proj", camera.getProjMatrix());
		shader.setMat4("view", camera.getViewMatrix());
		cube.draw();

		snprintf(txtB, 64, "%f", glfwGetTime());

		control.depthTest(false);
		control.transparency(true);
		gui.draw(glm::vec2(0.4,0.4));

		control.swapBuffers();
	}
	return 0;
}