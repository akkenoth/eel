#include "Cube.h"

using glm::vec3;
using glm::vec4;

Cube::Cube() {}
Cube::~Cube() {}

void Cube::create() {
	time(&timer);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	std::vector<VertexFormat> vertices;
	// Front face
	vertices.push_back(VertexFormat(vec3(-1.0, -1.0, 1.0), vec4( 0.0,  0.0, 1.0, 1.0)));
	vertices.push_back(VertexFormat(vec3(1.0, -1.0, 1.0), vec4(1.0,  0.0, 1.0, 1.0)));
	vertices.push_back(VertexFormat(vec3(1.0, 1.0, 1.0), vec4(1.0, 1.0, 1.0, 1.0)));
	vertices.push_back(VertexFormat(vec3(-1.0, 1.0, 1.0), vec4( 0.0, 1.0, 1.0, 1.0)));
	vertices.push_back(VertexFormat(vec3(1.0, 1.0, 1.0), vec4(1.0, 1.0, 1.0, 1.0)));
	vertices.push_back(VertexFormat(vec3(-1.0, -1.0, 1.0), vec4( 0.0,  0.0, 1.0, 1.0)));
	// Right face
	vertices.push_back(VertexFormat(vec3(1.0, 1.0, 1.0), vec4(1.0, 1.0, 1.0, 1.0)));
	vertices.push_back(VertexFormat(vec3(1.0, 1.0, -1.0), vec4(1.0, 1.0,  0.0, 1.0)));
	vertices.push_back(VertexFormat(vec3(1.0, -1.0, -1.0), vec4(1.0,  0.0 , 0.0, 1.0)));
	vertices.push_back(VertexFormat(vec3(1.0, 1.0, 1.0), vec4(1.0, 1.0, 1.0, 1.0)));
	vertices.push_back(VertexFormat(vec3(1.0, -1.0, -1.0), vec4(1.0,  0.0, 0.0, 1.0)));
	vertices.push_back(VertexFormat(vec3(1.0, -1.0, 1.0), vec4(1.0,  0.0, 1.0, 1.0)));
	// Back face
	vertices.push_back(VertexFormat(vec3(-1.0, -1.0, -1.0), vec4( 0.0,  0.0,  0.0, 1.0)));
	vertices.push_back(VertexFormat(vec3(1.0, -1.0, -1.0), vec4(1.0,  0.0,  0.0, 1.0)));
	vertices.push_back(VertexFormat(vec3(1.0, 1.0, -1.0), vec4(1.0, 1.0,  0.0, 1.0)));
	vertices.push_back(VertexFormat(vec3(-1.0, -1.0, -1.0), vec4( 0.0,  0.0,  0.0, 1.0)));
	vertices.push_back(VertexFormat(vec3(1.0, 1.0, -1.0), vec4(1.0, 1.0,  0.0, 1.0)));
	vertices.push_back(VertexFormat(vec3(-1.0, 1.0, -1.0), vec4( 0.0, 1.0,  0.0, 1.0)));
	// Left face
	vertices.push_back(VertexFormat(vec3(-1.0, -1.0, -1.0), vec4( 0.0, 0.0, 0.0, 1.0)));
	vertices.push_back(VertexFormat(vec3(-1.0, -1.0, 1.0), vec4( 0.0,  0.0, 1.0, 1.0)));
	vertices.push_back(VertexFormat(vec3(-1.0, 1.0, 1.0), vec4( 0.0, 1.0, 1.0, 1.0)));
	vertices.push_back(VertexFormat(vec3(-1.0, -1.0, -1.0), vec4( 0.0,  0.0,  0.0, 1.0)));
	vertices.push_back(VertexFormat(vec3(-1.0, 1.0, 1.0), vec4( 0.0, 1.0, 1.0, 1.0)));
	vertices.push_back(VertexFormat(vec3(-1.0, 1.0, -1.0), vec4(0.0, 1.0, 0.0, 1.0)));
	// Top face
	vertices.push_back(VertexFormat(vec3(1.0, 1.0, 1.0), vec4(1.0, 1.0, 1.0, 1.0)));
	vertices.push_back(VertexFormat(vec3(-1.0, 1.0, 1.0), vec4( 0.0, 1.0, 1.0, 1.0)));
	vertices.push_back(VertexFormat(vec3(1.0, 1.0, -1.0), vec4(1.0, 1.0,  0.0, 1.0)));
	vertices.push_back(VertexFormat(vec3(-1.0, 1.0, 1.0), vec4( 0.0, 1.0, 1.0, 1.0)));
	vertices.push_back(VertexFormat(vec3(1.0, 1.0, -1.0), vec4(1.0, 1.0,  0.0, 1.0)));
	vertices.push_back(VertexFormat(vec3(-1.0, 1.0, -1.0), vec4( 0.0, 1.0, 0.0, 1.0)));
	// Bottom face
	vertices.push_back(VertexFormat(vec3(-1.0, -1.0, -1.0), vec4( 0.0,  0.0, 0.0, 1.0)));
	vertices.push_back(VertexFormat(vec3(1.0, -1.0, -1.0), vec4(1.0,  0.0,  0.0, 1.0)));
	vertices.push_back(VertexFormat(vec3(-1.0, -1.0, 1.0), vec4( 0.0,  0.0, 1.0, 1.0)));
	vertices.push_back(VertexFormat(vec3(1.0, -1.0, -1.0), vec4(1.0,  0.0, 0.0, 1.0)));
	vertices.push_back(VertexFormat(vec3(-1.0, -1.0, 1.0), vec4( 0.0,  0.0, 1.0, 1.0)));
	vertices.push_back(VertexFormat(vec3(1.0, -1.0, 1.0), vec4(1.0,  0.0, 1.0, 1.0)));
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 36, &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::position)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::color)));
	//?
	glBindVertexArray(0);

	this->vao = vao;
	this->vbos.push_back(vbo);
	rotationSpeed = vec3(0.0, 90.0, 0.0);
	rotation = vec3(0.0, 0.0, 0.0);
}

void Cube::update() {}

void Cube::draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix) {
	rotation = 0.01f * rotationSpeed + rotation;

	vec3 rotationSin = vec3(rotation.x * M_PI / 180, rotation.y * M_PI / 180, rotation.z * M_PI / 180);
	glUseProgram(program);
	glUniform3f(glGetUniformLocation(program, "rotation"), rotationSin.x, rotationSin.y, rotationSin.z);
	glUniformMatrix4fv(glGetUniformLocation(program, "viewMatrix"), 1, false, &viewMatrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "projectionMatrix"), 1, false, &projectionMatrix[0][0]);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
