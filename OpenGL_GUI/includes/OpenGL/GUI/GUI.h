#ifndef GUI_H_
#define GUI_H_

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "../Mesh.h"
#include "../Buffer.h"
#include "../Shader.h"
#include "../Texture.h"
#include <iostream>

enum elementType {
	GUI_TEXT,
	GUI_SLIDER,
	GUI_BUTTON
};

struct GUIelement {
	elementType type;
	char* string;
	int stringSize;
	double* data;
	double min;
	double max;
	int side;
};


class GUI {
public:
	GUI(int screen_width, int screen_height, double element_width, double element_height);
	void draw(glm::vec2 pos);
	void update(glm::vec2 mouse, bool mouseDown);
	void show(bool state);

	void addText(char* str, int stringSize);
	void addSlider(double* data, double min, double max);
	void addButton(char* str, int stringSize, double* data);
	void removeAt(int index);
	void remeveAll();
	~GUI();
private:
	bool isShow;
	double aspectRatio;
	double element_width;
	double element_height;
	double element_aspectRatio;
	std::vector<GUIelement> elements;
	Buffer buffer{ GL_SHADER_STORAGE_BUFFER, 256 * sizeof(GLfloat), nullptr, GL_STREAM_DRAW };
	Texture font{ "includes/OpenGL/GUI/fontSDF.png", GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, true };
	Shader shader{ "includes/OpenGL/GUI/GUI.vert", "includes/OpenGL/GUI/GUI.frag", nullptr, false };
	Mesh mesh;
};

#endif 