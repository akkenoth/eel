#include "Triangle.h"

Triangle::Triangle() {}

Triangle::~Triangle() {}

void Triangle::create() {
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	std::vector<VertexFormat> vertices;
	vertices.push_back(VertexFormat(glm::vec3(-0.25, -0.25, 0.0), glm::vec4(1, 0, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(0.0, 0.25, 0.0), glm::vec4(0, 0, 1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(0.25, -0.25, 0.0), glm::vec4(0, 1, 0, 1)));
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat)*3, &vertices[0], GL_STATIC_DRAW);
	// Qualifier (pipe) 0 - positions
	glEnableVertexAttribArray(0);
	// pipe 0, 3 values, floats, not normalized, offset between next items in array, offset from beggining of item
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::position)));
	// Q 1 - colors
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::color)));

	this->vao = vao;
	this->vbos.push_back(vbo);
}

void Triangle::update() {}

void Triangle::draw() {
	glUseProgram(program);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
