#version 330 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform vec3 rotation;

out vec4 color; // Goes to fragment shader

void main(void) {
	color = in_color;

	mat4 rotateX = mat4(1.0, 0.0, 0.0, 0.0,
		0.0, cos(rotation.x), sin(rotation.x), 0.0,
		0.0, -sin(rotation.x), cos(rotation.x), 0.0,
		0.0, 0.0, 0.0, 1.0);
	mat4 rotateY = mat4(cos(rotation.y), 0.0, -sin(rotation.y), 0.0,
		0.0, 1.0, 0.0, 0.0,
		sin(rotation.y), 0.0, cos(rotation.y), 0.0,
		0.0, 0.0, 0.0, 1.0);
	mat4 rotateZ = mat4(cos(rotation.z), -sin(rotation.z), 0.0, 0.0,
		sin(rotation.z), cos(rotation.z), 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0);		

	gl_Position = projectionMatrix * viewMatrix * rotateX * rotateY * rotateZ * vec4(in_position, 1.0);
}