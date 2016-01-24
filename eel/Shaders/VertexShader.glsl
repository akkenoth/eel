#version 330 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec4 in_color;
layout(location = 3) in vec2 in_texture;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelPosition;
uniform vec3 rotation;

// Goes to fragment shader, preserve names!
out vec3 worldPosition;
out vec3 worldNormal;
out vec2 textureCoords;
out vec4 color;

void main(void) {
	textureCoords = in_texture;
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
	mat4 rotationMatrix = rotateX * rotateY * rotateZ;
	
	// For fragment shader
	worldPosition = mat3(modelPosition * rotationMatrix) * in_position;
	worldNormal = normalize(mat3(modelPosition * rotationMatrix) * in_normal);

	gl_Position = projectionMatrix * viewMatrix * modelPosition * rotationMatrix * vec4(in_position, 1.0);
}