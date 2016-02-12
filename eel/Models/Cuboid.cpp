#include "Cuboid.h"

Cuboid::Cuboid() : RenderModel() {}
Cuboid::~Cuboid() {}

void Cuboid::create(GLfloat sizeX, GLfloat sizeY, GLfloat sizeZ, const glm::vec4& color) {
	// Vertices
	std::vector<VertexFormat> vertices;
	glm::vec3 normal;
	// Front face
	normal = glm::vec3(0.0, 0.0, 1.0);
	vertices.push_back(VertexFormat(glm::vec3(-sizeX * 0.5f, -sizeY * 0.5f, sizeZ * 0.5f), normal, glm::vec2(0, 0), glm::vec4(color)));
	vertices.push_back(VertexFormat(glm::vec3(sizeX * 0.5f, -sizeY * 0.5f, sizeZ * 0.5f), normal, glm::vec2(1, 0), glm::vec4(color)));
	vertices.push_back(VertexFormat(glm::vec3(sizeX * 0.5f, sizeY * 0.5f, sizeZ * 0.5f), normal, glm::vec2(1, 1), glm::vec4(color)));
	vertices.push_back(VertexFormat(glm::vec3(-sizeX * 0.5f, sizeY * 0.5f, sizeZ * 0.5f), normal, glm::vec2(0, 1), glm::vec4(color)));
	// Right face
	normal = glm::vec3(1.0, 0.0, 0.0);
	vertices.push_back(VertexFormat(glm::vec3(sizeX * 0.5f, sizeY * 0.5f, sizeZ * 0.5f), normal, glm::vec2(0, 0), glm::vec4(color)));
	vertices.push_back(VertexFormat(glm::vec3(sizeX * 0.5f, sizeY * 0.5f, -sizeZ * 0.5f), normal, glm::vec2(1, 0), glm::vec4(color)));
	vertices.push_back(VertexFormat(glm::vec3(sizeX * 0.5f, -sizeY * 0.5f, -sizeZ * 0.5f), normal, glm::vec2(1, 1), glm::vec4(color)));
	vertices.push_back(VertexFormat(glm::vec3(sizeX * 0.5f, -sizeY * 0.5f, sizeZ * 0.5f), normal, glm::vec2(0, 1), glm::vec4(color)));
	// Back face
	normal = glm::vec3(0.0, 0.0, -1.0);
	vertices.push_back(VertexFormat(glm::vec3(-sizeX * 0.5f, -sizeY * 0.5f, -sizeZ * 0.5f), normal, glm::vec2(0, 0), glm::vec4(color)));
	vertices.push_back(VertexFormat(glm::vec3(sizeX * 0.5f, -sizeY * 0.5f, -sizeZ * 0.5f), normal, glm::vec2(1, 0), glm::vec4(color)));
	vertices.push_back(VertexFormat(glm::vec3(sizeX * 0.5f, sizeY * 0.5f, -sizeZ * 0.5f), normal, glm::vec2(1, 1), glm::vec4(color)));
	vertices.push_back(VertexFormat(glm::vec3(-sizeX * 0.5f, sizeY * 0.5f, -sizeZ * 0.5f), normal, glm::vec2(0, 1), glm::vec4(color)));
	// Left face
	normal = glm::vec3(-1.0, 0.0, 0.0);
	vertices.push_back(VertexFormat(glm::vec3(-sizeX * 0.5f, -sizeY * 0.5f, -sizeZ * 0.5f), normal, glm::vec2(0, 0), glm::vec4(color)));
	vertices.push_back(VertexFormat(glm::vec3(-sizeX * 0.5f, -sizeY * 0.5f, sizeZ * 0.5f), normal, glm::vec2(1, 0), glm::vec4(color)));
	vertices.push_back(VertexFormat(glm::vec3(-sizeX * 0.5f, sizeY * 0.5f, sizeZ * 0.5f), normal, glm::vec2(1, 1), glm::vec4(color)));
	vertices.push_back(VertexFormat(glm::vec3(-sizeX * 0.5f, sizeY * 0.5f, -sizeZ * 0.5f), normal, glm::vec2(0, 1), glm::vec4(color)));
	// Top face
	normal = glm::vec3(0.0, 1.0, 0.0);
	vertices.push_back(VertexFormat(glm::vec3(sizeX * 0.5f, sizeY * 0.5f, sizeZ * 0.5f), normal, glm::vec2(0, 0), glm::vec4(color)));
	vertices.push_back(VertexFormat(glm::vec3(-sizeX * 0.5f, sizeY * 0.5f, sizeZ * 0.5f), normal, glm::vec2(1, 0), glm::vec4(color)));
	vertices.push_back(VertexFormat(glm::vec3(-sizeX * 0.5f, sizeY * 0.5f, -sizeZ * 0.5f), normal, glm::vec2(1, 1), glm::vec4(color)));
	vertices.push_back(VertexFormat(glm::vec3(sizeX * 0.5f, sizeY * 0.5f, -sizeZ * 0.5f), normal, glm::vec2(0, 1), glm::vec4(color)));
	// Bottom face
	normal = glm::vec3(0.0, -1.0, 0.0);
	vertices.push_back(VertexFormat(glm::vec3(-sizeX * 0.5f, -sizeY * 0.5f, -sizeZ * 0.5f), normal, glm::vec2(0, 0), glm::vec4(color)));
	vertices.push_back(VertexFormat(glm::vec3(sizeX * 0.5f, -sizeY * 0.5f, -sizeZ * 0.5f), normal, glm::vec2(1, 0), glm::vec4(color)));
	vertices.push_back(VertexFormat(glm::vec3(sizeX * 0.5f, -sizeY * 0.5f, sizeZ * 0.5f), normal, glm::vec2(1, 1), glm::vec4(color)));
	vertices.push_back(VertexFormat(glm::vec3(-sizeX * 0.5f, -sizeY * 0.5f, sizeZ * 0.5f), normal, glm::vec2(0, 1), glm::vec4(color)));

	// Indices
	std::vector<GLuint> indices = {
		0, 1, 2, 0, 2, 3,
		4, 5, 6, 4, 6, 7,
		8, 9, 10, 8, 10, 11,
		12, 13, 14, 12, 14, 15,
		16, 17, 18, 16, 18, 19,
		20, 21, 22, 20, 22, 23
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

void Cuboid::update(const float totalTimePassed, const float deltaTime, const bool force) {
	if(animated) {
		rotate(deltaTime);
	}
}

void Cuboid::draw(const GLuint program) {
	glBindVertexArray(vao);

	setPositionUniforms(program);
	setMaterialUniforms(program);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}
