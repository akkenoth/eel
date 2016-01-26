#include "Skybox.h"

Skybox::Skybox() {}

Skybox::~Skybox() {}

void Skybox::create(GLfloat size) {
	std::vector<VertexFormat> vertices;
	GLfloat halfSize = size / 2.0f;
	// Front face
	vertices.push_back(VertexFormat(glm::vec3(-halfSize, -halfSize, halfSize), glm::vec2(1.0f, 0.334f)));
	vertices.push_back(VertexFormat(glm::vec3(halfSize, -halfSize, halfSize), glm::vec2(0.75f, 0.334f)));
	vertices.push_back(VertexFormat(glm::vec3(halfSize, halfSize, halfSize), glm::vec2(0.75f, 0.666f)));
	vertices.push_back(VertexFormat(glm::vec3(-halfSize, halfSize, halfSize), glm::vec2(1.0f, 0.666f)));
	// Right face
	vertices.push_back(VertexFormat(glm::vec3(halfSize, halfSize, halfSize), glm::vec2(0.75f, 0.666f)));
	vertices.push_back(VertexFormat(glm::vec3(halfSize, halfSize, -halfSize), glm::vec2(0.5f, 0.666f)));
	vertices.push_back(VertexFormat(glm::vec3(halfSize, -halfSize, -halfSize), glm::vec2(0.5f, 0.334f)));
	vertices.push_back(VertexFormat(glm::vec3(halfSize, -halfSize, halfSize), glm::vec2(0.75f, 0.334f)));
	// Back face
	vertices.push_back(VertexFormat(glm::vec3(-halfSize, -halfSize, -halfSize), glm::vec2(0.25f, 0.334f)));
	vertices.push_back(VertexFormat(glm::vec3(halfSize, -halfSize, -halfSize), glm::vec2(0.5f, 0.334f)));
	vertices.push_back(VertexFormat(glm::vec3(halfSize, halfSize, -halfSize), glm::vec2(0.5f, 0.666f)));
	vertices.push_back(VertexFormat(glm::vec3(-halfSize, halfSize, -halfSize), glm::vec2(0.25f, 0.666f)));
	// Left face
	vertices.push_back(VertexFormat(glm::vec3(-halfSize, -halfSize, -halfSize), glm::vec2(0.25f, 0.334f)));
	vertices.push_back(VertexFormat(glm::vec3(-halfSize, -halfSize, halfSize), glm::vec2(0.0f, 0.334f)));
	vertices.push_back(VertexFormat(glm::vec3(-halfSize, halfSize, halfSize), glm::vec2(0.0f, 0.666f)));
	vertices.push_back(VertexFormat(glm::vec3(-halfSize, halfSize, -halfSize), glm::vec2(0.25f, 0.666f)));
	// Top face
	vertices.push_back(VertexFormat(glm::vec3(halfSize, halfSize, halfSize), glm::vec2(0.499f, 1.0f)));
	vertices.push_back(VertexFormat(glm::vec3(-halfSize, halfSize, halfSize), glm::vec2(0.251f, 1.0f)));
	vertices.push_back(VertexFormat(glm::vec3(-halfSize, halfSize, -halfSize), glm::vec2(0.251f, 0.666f)));
	vertices.push_back(VertexFormat(glm::vec3(halfSize, halfSize, -halfSize), glm::vec2(0.499f, 0.666f)));
	// Bottom face
	vertices.push_back(VertexFormat(glm::vec3(-halfSize, -halfSize, -halfSize), glm::vec2(0.251f, 0.334f)));
	vertices.push_back(VertexFormat(glm::vec3(halfSize, -halfSize, -halfSize), glm::vec2(0.499f, 0.334f)));
	vertices.push_back(VertexFormat(glm::vec3(halfSize, -halfSize, halfSize), glm::vec2(0.499f, 0.0f)));
	vertices.push_back(VertexFormat(glm::vec3(-halfSize, -halfSize, halfSize), glm::vec2(0.251f, 0.0f)));

	// Indices (same order as vertices)
	std::vector<GLuint> indices = {
		0, 1, 2, 0, 2, 3,
		4, 5, 6, 4, 6, 7,
		8, 9, 10, 8, 10, 11,
		12, 13, 14, 12, 14, 15,
		16, 17, 18, 16, 18, 19,
		20, 21, 22, 20, 22, 23};

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

void Skybox::update(const float totalTimePassed, const float deltaTime) {}

void Skybox::draw(const GLuint program) {
	glBindVertexArray(vao);

	setPositionUniforms(program);
	setMaterialUniforms(program);

	// Draw
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}
