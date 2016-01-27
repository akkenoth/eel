#include "Cuboid.h"

Cuboid::Cuboid() {}
Cuboid::~Cuboid() {}

void Cuboid::create(GLfloat sizeX, GLfloat sizeY, GLfloat sizeZ, const glm::vec4& color) {
	// Vertices
	std::vector<VertexFormat> vertices;
	// Top face
	vertices.push_back(VertexFormat(glm::vec3(sizeX * 0.5f, sizeY * 0.5f, sizeZ * 0.5f), glm::vec2(1, 1), glm::vec4(color)));
	vertices.push_back(VertexFormat(glm::vec3(-sizeX * 0.5f, sizeY * 0.5f, sizeZ * 0.5f), glm::vec2(1, 0), glm::vec4(color)));
	vertices.push_back(VertexFormat(glm::vec3(-sizeX * 0.5f, sizeY * 0.5f, -sizeZ * 0.5f), glm::vec2(0, 0), glm::vec4(color)));
	vertices.push_back(VertexFormat(glm::vec3(sizeX * 0.5f, sizeY * 0.5f, -sizeZ * 0.5f), glm::vec2(0, 1), glm::vec4(color)));
	// Bottom face
	vertices.push_back(VertexFormat(glm::vec3(sizeX * 0.5f, -sizeY * 0.5f, sizeZ * 0.5f), glm::vec2(0, 0), glm::vec4(color)));
	vertices.push_back(VertexFormat(glm::vec3(-sizeX * 0.5f, -sizeY * 0.5f, sizeZ * 0.5f), glm::vec2(0, 1), glm::vec4(color)));
	vertices.push_back(VertexFormat(glm::vec3(-sizeX * 0.5f, -sizeY * 0.5f, -sizeZ * 0.5f), glm::vec2(1, 1), glm::vec4(color)));
	vertices.push_back(VertexFormat(glm::vec3(sizeX * 0.5f, -sizeY * 0.5f, -sizeZ * 0.5f), glm::vec2(1, 0), glm::vec4(color)));

	// Indices
	std::vector<GLuint> indices = {
		0, 1, 2, 0, 2, 3, //top
		6, 5, 4, 7, 6, 4, //bottom
		0, 4, 5, 0, 5, 1, //right
		1, 5, 6, 1, 6, 2, //front
		2, 6, 7, 2, 7, 3, //left
		3, 7, 4, 3, 4, 0 //back
		};

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexFormat), &vertices[0], GL_STATIC_DRAW);
	GLuint ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	setAttribPointers();

	this->vao = vao;
	this->vbos.push_back(vbo);
	this->vbos.push_back(ibo);
}

void Cuboid::update(const float totalTimePassed, const float deltaTime) {}

void Cuboid::draw(const GLuint program) {
	glBindVertexArray(vao);

	setPositionUniforms(program);
	setMaterialUniforms(program);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}
