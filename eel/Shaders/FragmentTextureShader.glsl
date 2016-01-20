#version 430 core

layout(location = 0) out vec4 out_color; // To framebuffer, color location

uniform sampler2D texture1;

in vec2 textureCoords;

void main(void) {
	out_color = texture(texture1, textureCoords);
}