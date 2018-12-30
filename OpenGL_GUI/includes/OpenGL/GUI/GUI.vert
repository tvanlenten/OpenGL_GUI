#version 430 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoords;

out vec2 uv;

uniform vec2 pos; //0.0 to 1.0
uniform vec2 scale;
uniform float aspectRatio;

void main() {
	uv = vec2(texCoords.x, 1.0 - texCoords.y);

	vec2 p = position * scale * 2.0;
	p = p + vec2(-1.0, 1.0 - scale.y*2.0);
	p = p + vec2(pos.x, -pos.y)*2.0;

    gl_Position = vec4(p, 0.0, 1.0); 
} 