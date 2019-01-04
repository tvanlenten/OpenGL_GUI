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

enum textSide {
	GUI_LEFT_SIDE,
	GUI_CENTER_SIDE,
	GUI_RIGHT_SIDE
};

struct GUIelement {
	elementType type;
	char* string;
	double charSize;
	double* data;
	double min;
	double max;
	int side;
	glm::vec3 textCol;
	glm::vec3 activeCol;
};


class GUI {
public:
	GUI(int screen_width, int screen_height, double element_width, double element_height, glm::vec3 backgroundCol, double transparency);
	void draw();
	void update(glm::vec4 mouse, bool mouseDown);

	/*
		adds a text element with the default background color
	*/
	void addText(char* str, double charSize, int side, glm::vec3 textCol);

	/*
		adds a text element with the specified background color
	*/
	void addText(char* str, double charSize, int side, glm::vec3 textCol, glm::vec3 activeCol);
	
	void addSlider(char* str, double charSize, double* data, double min, double max, int side, glm::vec3 textCol, glm::vec3 sliderCol);
	void addButton(char* str, double charSize, double* data, int side, glm::vec3 textCol, glm::vec3 buttonCol);
	void removeAt(int index);
	void remeveAll();

	bool insideGUI(glm::vec2 p);

	void setPosition(glm::vec2 position);
	void setSize(glm::vec2 size);
	void setBackgroundColor(glm::vec3 color);
	void setTransparency(double transparancy);


	~GUI();
private:
	double aspectRatio;
	double element_width;
	double element_height;
	double element_aspectRatio;
	bool mouseAlreadyDown;
	glm::vec2 position;
	glm::vec3 backgroundCol;
	double transparency;
	std::vector<GUIelement> elements;
	Buffer buffer{ GL_SHADER_STORAGE_BUFFER, 256 * sizeof(GLfloat), nullptr, GL_STREAM_DRAW };
	Texture font{ "includes/OpenGL/GUI/fontSDF.png", GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, true };
	Shader shader{ "includes/OpenGL/GUI/GUI.vert", "includes/OpenGL/GUI/GUI.frag", nullptr, false };
	Mesh mesh;
};

#endif 