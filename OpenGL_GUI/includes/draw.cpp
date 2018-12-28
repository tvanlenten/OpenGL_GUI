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


	GUI gui(width, height, 0.1, 0.02);

	
	control.depthTest(true);
	control.cull(GL_FRONT);
	//control.wireframe(true);
	control.showMouse(true);
	while (!control.shouldQuit()) {
		control.update();
		camera.update();
		gui.update(glm::vec2(getMouse().x, getMouse().y), isMouseLeftDown());

		screen.use();
		screen.clear();

		control.transparency(false);
		control.depthTest(true);
		shader.use();
		shader.setFloat("time", control.getTime());
		shader.setMat4("proj", camera.getProjMatrix());
		shader.setMat4("view", camera.getViewMatrix());
		cube.draw();


		//control.depthTest(false);
		gui.draw(glm::vec2(0.0,0.0));

		control.swapBuffers();
	}
	return 0;
}