#version 430 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;

out vec2 uv;

uniform mat4 proj;
uniform mat4 view;

uniform float scale;

void main() {
	uv = texCoords;
    gl_Position = proj * view * vec4(position*scale, 1.0); 
} 