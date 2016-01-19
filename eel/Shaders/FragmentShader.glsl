#version 430 core

layout(location = 0) out vec4 out_color; // To framebuffer, color location

in vec4 color; // From vertex shader, name must be preserved between shaders!

void main(void) {
	out_color = color;
}