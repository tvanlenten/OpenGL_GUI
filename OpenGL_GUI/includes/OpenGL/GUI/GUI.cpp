#include "GUI.h"


GUI::GUI(int screen_width, int screen_height, double element_width, double element_height, glm::vec3 backgroundCol, double transparency) {
	this->aspectRatio = double(screen_height) / double(screen_width);
	this->element_width = element_width;
	this->element_height = element_height;
	this->element_aspectRatio = element_width / element_height;
	this->backgroundCol = backgroundCol;
	this->transparency = transparency;

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
	shader.setVec3("backgroundCol", this->backgroundCol);
	shader.setFloat("alphaVal", this->transparency);

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
	float data[256];
	shader.use();
	shader.setVec2("scale", glm::vec2(element_width, element_height));
	font.use(0);

	double py = 0.0;
	for (GUIelement element: elements) {

		if (element.type == GUI_SLIDER) {
			char str[256];
			int s = snprintf(str, 256, element.string, *element.data);
			for (int i = 0; i < s; i++) {
				data[i] = float(str[i]);
			}
			shader.setInt("stringCount", s);
		} else {
			int i = 0;
			while (element.string[i] != '\0') {
				data[i] = float(element.string[i]);
				i++;
			}
			shader.setInt("stringCount", i);
		}
		buffer.update(0, 256, data);

		glm::vec2 p = pos + glm::vec2(0.0, py);

		double sliderVal = 0.0;
		if (element.data) {
			sliderVal = *element.data;
			sliderVal = (sliderVal - element.min) / (element.max - element.min);
		}
		if (element.type == GUI_TEXT && element.min == 0.0) {
			sliderVal = 1.0;
		}

		shader.setVec2("pos", p);
		shader.setFloat("charSize", element.charSize);
		shader.setFloat("sliderVal", sliderVal);
		shader.setInt("side", element.side);
		shader.setVec3("textCol", element.textCol);
		shader.setVec3("activeCol", element.activeCol);
		mesh.draw();
		py += element_height;
	}
}

void GUI::update(glm::vec2 pos, glm::vec2 mouse, bool mouseDown) {
	if(!mouseDown)mouseAlreadyDown = false;

	double py = 0.0;
	int i = 0;
	for (int i = 0; i < elements.size(); i++) {
		if (mouseDown && mouse.y > pos.y + element_height*i && mouse.y < pos.y + element_height*(i + 1)
				&& mouse.x > pos.x && mouse.x < pos.x + element_width) {
			if (elements[i].type == GUI_SLIDER) {
				double val = (mouse.x - pos.x) / element_width;
				val = glm::clamp(val, 0.0, 1.0);
				val = elements[i].min + val*(elements[i].max - elements[i].min);
				*elements[i].data = val;
			} else if (elements[i].type == GUI_BUTTON && !mouseAlreadyDown) {
				if (*elements[i].data == 1.0)
					*elements[i].data = 0.0;
				else
					*elements[i].data = 1.0;
			}
		}
	}

	if (mouseDown)mouseAlreadyDown = true;
}


void GUI::show(bool state) {
	isShow = state;
}

void GUI::addText(char* str, double charSize, int side, glm::vec3 textCol) {
	GUIelement element;
	element.type = GUI_TEXT;
	element.data = nullptr;
	element.charSize = charSize;
	element.string = str;
	element.min = -1.0;
	element.max = -1.0;
	element.side = side;
	element.textCol = textCol;
	element.activeCol = glm::vec3(0.0);
	elements.push_back(element);
}

void GUI::addText(char* str, double charSize, int side, glm::vec3 textCol, glm::vec3 activeCol) {
	GUIelement element;
	element.type = GUI_TEXT;
	element.data = nullptr;
	element.charSize = charSize;
	element.string = str;
	element.min = 0.0;
	element.max = -1.0;
	element.side = side;
	element.textCol = textCol;
	element.activeCol = activeCol;
	elements.push_back(element);
}

void GUI::addSlider(char* str, double charSize, double* data, double min, double max, int side, glm::vec3 textCol, glm::vec3 sliderCol) {
	GUIelement element;
	element.type = GUI_SLIDER;
	element.data = data;
	element.charSize = charSize;
	element.string = str;
	element.min = min;
	element.max = max;
	element.side = side;
	element.textCol = textCol;
	element.activeCol = sliderCol;
	elements.push_back(element);
}

void GUI::addButton(char* str, double charSize, double* data, int side, glm::vec3 textCol, glm::vec3 buttonCol) {
	GUIelement element;
	element.type = GUI_BUTTON;
	element.data = data;
	element.charSize = charSize;
	element.string = str;
	element.min = 0.0;
	element.max = 1.0;
	element.side = side;
	element.textCol = textCol;
	element.activeCol = buttonCol;
	elements.push_back(element);
}

void GUI::removeAt(int index) {
	elements.erase(elements.begin() + index);
}

void GUI::remeveAll() {
	elements.clear();
}

GUI::~GUI() {
	elements.clear();
}
