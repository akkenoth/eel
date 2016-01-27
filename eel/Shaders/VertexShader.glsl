#version 330 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec4 in_color;
layout(location = 3) in vec2 in_texture;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelPosition;
// uniform mat4 modelPositionIT;
uniform mat4 rotationMatrix;
uniform vec3 rotation;

// Goes to fragment shader, preserve names!
out vec3 worldPosition;
out vec3 worldNormal;
out vec2 textureCoords;
out vec4 color;

void main(void) {
	textureCoords = in_texture;
	color = in_color;
	
	// For fragment shader
	vec4 position = modelPosition * rotationMatrix * vec4(in_position, 1.0);
	worldPosition = vec3(position);
	gl_Position = projectionMatrix * viewMatrix * position;

	worldNormal = normalize(vec3(modelPosition * rotationMatrix * vec4(in_normal, 0.0)));
}