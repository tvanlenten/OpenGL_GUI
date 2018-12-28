#include "GUI.h"


GUI::GUI(int screen_width, int screen_height, double element_width, double element_height) {
	this->aspectRatio = double(screen_height) / double(screen_width);
	this->element_width = element_width;
	this->element_height = element_height;
	this->element_aspectRatio = element_width / element_height;

	GLfloat textVerts[] = {
		1.0f, 0.0f,  1.0f, 0.0f,
		0.0f, 0.0f,  0.0f, 0.0f,
		0.0f,  1.0f,  0.0f, 1.0f,

		1.0f,  1.0f,  1.0f, 1.0f,
		1.0f, 0.0f,  1.0f, 0.0f,
		0.0f,  1.0f,  0.0f, 1.0f,
	};

	shader.use();
	shader.setInt("fontTexture", 0);
	shader.setFloat("aspectRatio", this->aspectRatio);
	shader.setFloat("boxAspectRatio", this->element_aspectRatio);

	buffer.bind();
	buffer.bindTo(2);
	buffer.unbind();


	Buffer meshData(GL_ARRAY_BUFFER, 24 * sizeof(GLfloat), textVerts, GL_STATIC_DRAW);
	meshData.bind();
	mesh.bind();
	mesh.setVextexSize(6);
	mesh.attach(GL_FLOAT, 2, 4 * sizeof(GLfloat), 0, false);
	mesh.attach(GL_FLOAT, 2, 4 * sizeof(GLfloat), 2 * sizeof(GLfloat), false);
	mesh.unbind();
}

void GUI::draw(glm::vec2 pos) {
	double rr = glm::mod(glfwGetTime()*0.1, 1.0);

	float data[256];
	char textData[256];
	int s = snprintf(textData, 256, "Button ssss");
	for (int i = 0; i < s; i++) {
		data[i] = float(textData[i]);
	}
	shader.use();
	shader.setInt("stringCount", s);
	buffer.update(0, 256, data);

	shader.use();
	font.use(0);
	double py = 0.0;
	for (int i = 0; i < 10; i++) {

		shader.setVec2("pos", glm::vec2(0.0, py));
		shader.setVec2("scale", glm::vec2(element_width, element_height));
		shader.setFloat("charSize", 0.05);
		shader.setFloat("sliderVal", floor(rr*2.0));
		shader.setInt("side", i%3);
		mesh.draw();
		py += element_height;
	}
}
void GUI::update(glm::vec2 mouse, bool mouseDown) {

}

void GUI::show(bool state) {
	isShow = state;
}


void GUI::addText(char* str, int stringSize) {
	GUIelement element;
	element.type = GUI_TEXT;
	element.data = nullptr;
	element.string = str;
	element.stringSize = stringSize;
	element.min = -1.0;
	element.max = -1.0;
	elements.push_back(element);
}
void GUI::addSlider(double* data, double min, double max) {
	GUIelement element;
	element.type = GUI_SLIDER;
	element.data = data;
	element.string = new char[64];
	element.stringSize = snprintf(element.string, 64, "%f", &data);
	element.min = min;
	element.max = max;
	elements.push_back(element);
}
void GUI::addButton(char* str, int stringSize, double* data) {
	GUIelement element;
	element.type = GUI_BUTTON;
	element.data = data;
	element.string = str;
	element.stringSize = stringSize;
	element.min = -1.0;
	element.max = -1.0;
	elements.push_back(element);
}
void GUI::removeAt(int index) {
	elements.erase(elements.begin() + index);
}
void GUI::remeveAll() {
	elements.clear();
}

GUI::~GUI() {
	for (GUIelement element : elements) {
		if (element.type == GUI_SLIDER) {
			delete[] element.string;
		}
	}
	elements.clear();
}
