#include "OpenGL\OpenGL.h"

#define width 1920
#define height 1080

//#define width 1280
//#define height 720


int main() {
	Control control(width, height, "OpenGL GUI", true);
	FrameBuffer screen(width, height);
	Camera camera(width, height, glm::vec3(-0.1f, 1.0f, -0.1f), 90.0f, 0.1f, 100.0f, 0.1f, 0.1f);
	GUI gui(width, height, 0.11, 0.04, glm::vec3(0.05), 0.8);

	//Texture tex("textures/t1.jpg", GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, true);
	Shader shader("shaders/posUV3D.vert", "shaders/rayRasterBackface.frag", nullptr, false);
	shader.use();
	shader.setFloat("MAX_DIST", 3.0);
	shader.setFloat("PRECIS", 0.001);
	shader.setInt("MAX_RAY_STEPS", 256);


	//ADD GUI ELEMENTS
	gui.addText("Simple GUI", 0.05, GUI_CENTER_SIDE, glm::vec3(1.0), glm::vec3(0.0,0.0,1.0));
	
	double ampA = 0.5;
	gui.addSlider("ampA: %f", 0.05, &ampA, 0.0, 1.0, GUI_LEFT_SIDE, glm::vec3(1.0), glm::vec3(0.572, 0.007, 0.529));
	double feqA = 1.0;
	gui.addSlider("feqA: %f", 0.05, &feqA, 0.1, 32.0, GUI_LEFT_SIDE, glm::vec3(1.0), glm::vec3(0.031, 0.666, 0.619));

	double ampB = 0.25;
	gui.addSlider("ampB: %f", 0.05, &ampB, 0.0, 1.0, GUI_LEFT_SIDE, glm::vec3(1.0), glm::vec3(0.572, 0.007, 0.529));
	double feqB = 2.0;
	gui.addSlider("feqB: %f", 0.05, &feqB, 0.1, 32.0, GUI_LEFT_SIDE, glm::vec3(1.0), glm::vec3(0.031, 0.666, 0.619));

	double ampC = 0.125;
	gui.addSlider("ampC: %f", 0.05, &ampC, 0.0, 1.0, GUI_LEFT_SIDE, glm::vec3(1.0), glm::vec3(0.572, 0.007, 0.529));
	double feqC = 4.0;
	gui.addSlider("feqC: %f", 0.05, &feqC, 0.1, 32.0, GUI_LEFT_SIDE, glm::vec3(1.0), glm::vec3(0.031, 0.666, 0.619));

	double ampD = 0.0625;
	gui.addSlider("ampD: %f", 0.05, &ampD, 0.0, 1.0, GUI_LEFT_SIDE, glm::vec3(1.0), glm::vec3(0.572, 0.007, 0.529));
	double feqD = 8.0;
	gui.addSlider("feqD: %f", 0.05, &feqD, 0.1, 32.0, GUI_LEFT_SIDE, glm::vec3(1.0), glm::vec3(0.031, 0.666, 0.619));

	double ampE = 0.03125;
	gui.addSlider("ampE: %f", 0.05, &ampE, 0.0, 1.0, GUI_LEFT_SIDE, glm::vec3(1.0), glm::vec3(0.572, 0.007, 0.529));
	double feqE = 16.0;
	gui.addSlider("feqE: %f", 0.05, &feqE, 0.1, 32.0, GUI_LEFT_SIDE, glm::vec3(1.0), glm::vec3(0.031, 0.666, 0.619));


	gui.addText("World Offset", 0.05, GUI_CENTER_SIDE, glm::vec3(1.0), glm::vec3(0.0, 0.0, 1.0));

	double offsetX = 0.0;
	gui.addSlider("offsetX: %f", 0.05, &offsetX, -10.0, 10.0, GUI_LEFT_SIDE, glm::vec3(1.0), glm::vec3(1.0,0.0,0.2));
	double offsetY = 0.0;
	gui.addSlider("offsetY: %f", 0.05, &offsetY, -10.0, 10.0, GUI_LEFT_SIDE, glm::vec3(1.0), glm::vec3(0.2, 1.0, 0.0));
	double offsetZ = 0.0;
	gui.addSlider("offsetZ: %f", 0.05, &offsetZ, -10.0, 10.0, GUI_LEFT_SIDE, glm::vec3(1.0), glm::vec3(0.0, 0.2, 1.0));


	Mesh cube;
	cube.createCube();


	//control.wireframe(true);
	control.hideMouse();
	while (!control.shouldQuit()) {
		control.update();
		camera.update(&control);
		gui.update(control.getNormalMouse(), control.leftMousePressed());

		if (control.keyPressed(GLFW_KEY_C)) {
			control.hideMouse();
		}
		if (control.keyPressed(GLFW_KEY_G)) {
			control.showMouse();
		}

		screen.use();
		screen.clear();

		control.cull(GL_BACK);
		control.depthTest(true);
		control.transparency(false);
		shader.use();
		shader.setMat4("proj", camera.getProjMatrix());
		shader.setMat4("view", camera.getViewMatrix());
		shader.setVec3("camera", camera.getPosition());

		shader.setFloat("ampA", ampA);
		shader.setFloat("feqA", feqA);
		shader.setFloat("ampB", ampB);
		shader.setFloat("feqB", feqB);
		shader.setFloat("ampC", ampC);
		shader.setFloat("feqC", feqC);
		shader.setFloat("ampD", ampD);
		shader.setFloat("feqD", feqD);
		shader.setFloat("ampE", ampE);
		shader.setFloat("feqE", feqE);
		shader.setVec3("offset", glm::vec3(offsetX, offsetY, offsetZ));



		cube.draw();

		control.cull(GL_FRONT);
		control.depthTest(false);
		control.transparency(true);
		gui.draw();

		control.swapBuffers();
	}
	return 0;
}
