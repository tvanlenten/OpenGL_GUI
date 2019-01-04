#include "OpenGL\OpenGL.h"

#define width 1920
#define height 1080

//#define width 1280
//#define height 720


int main() {
	Control control(width, height, "OpenGL GUI", true);
	FrameBuffer screen(width, height);
	Camera camera(width, height, glm::vec3(-0.1f, 1.0f, -0.1f), 90.0f, 0.1f, 100.0f, 0.1f, 0.1f);
	GUI gui(width, height, 0.2, 0.05, glm::vec3(0.05), 0.8);

	//Texture tex("textures/t1.jpg", GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, true);
	Shader shader("shaders/vertex.vert", "shaders/frag.frag", nullptr, false);
	shader.use();
	

	gui.addText("Simple GUI", 0.05, GUI_CENTER_SIDE, glm::vec3(1.0), glm::vec3(0.0,0.0,1.0));

	char txtStr[64];
	gui.addText(txtStr, 0.02, GUI_LEFT_SIDE, glm::vec3(1.0));

	double sliderVal = 1.0;
	gui.addSlider("Scale: %f", 0.05, &sliderVal, 0.01, 5.0, GUI_LEFT_SIDE, glm::vec3(1.0), glm::vec3(1.0,1.0,0.0));
	
	double buttonVal = 1.0;
	gui.addButton("Button", 0.05, &buttonVal, GUI_LEFT_SIDE, glm::vec3(1.0), glm::vec3(0.0, 1.0, 1.0));

	Mesh cube;
	cube.createCube();


	control.cull(GL_FRONT);
	//control.wireframe(true);
	control.hideMouse();
	while (!control.shouldQuit()) {
		control.update();
		camera.update(&control);
		gui.update(control.getNormalMouse(), control.leftMousePressed());
		sprintf_s(txtStr, "time: %f", control.getTime());

		if (control.keyPressed(GLFW_KEY_C)) {
			control.hideMouse();
		}
		if (control.keyPressed(GLFW_KEY_G)) {
			control.showMouse();
		}

		screen.use();
		screen.clear();

		control.depthTest(true);
		control.transparency(false);
		shader.use();
		shader.setFloat("time", control.getTime());
		shader.setFloat("scale", sliderVal);
		shader.setMat4("proj", camera.getProjMatrix());
		shader.setMat4("view", camera.getViewMatrix());
		cube.draw();

		control.depthTest(false);
		control.transparency(true);
		gui.draw();

		control.swapBuffers();
	}
	return 0;
}
