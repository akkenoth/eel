#include "Cube.h"

Cube::Cube() {}
Cube::~Cube() {}

void Cube::create() {
	// Vertices
	std::vector<VertexFormat> vertices;
	// Front face
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0), glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, 1.0), glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0), glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, 1.0), glm::vec2(0, 1)));
	// Right face
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0), glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, -1.0), glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0), glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, 1.0), glm::vec2(0, 1)));
	// Back face
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0), glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0), glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, -1.0), glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, -1.0), glm::vec2(0, 1)));
	// Left face
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0), glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0), glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, 1.0), glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, -1.0), glm::vec2(0, 1)));
	// Top face
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0), glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, 1.0), glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, -1.0), glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, -1.0), glm::vec2(0, 1)));
	// Bottom face
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0), glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0), glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, 1.0), glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0), glm::vec2(0, 1)));

	// Indices (same order as vertices)
	std::vector<GLuint> indices = {0, 1, 2, 0, 2, 3,
		4, 5, 6, 4, 6, 7,
		8, 9, 10, 8, 10, 11,
		12, 13, 14, 12, 14, 15,
		16, 17, 18, 16, 18, 19,
		20, 21, 22, 20, 22, 23};

	time(&timer);

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

	// Vertices
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::position)));
	// Texture
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::texture)));
	
	// Finish
	glBindVertexArray(0);
	this->vao = vao;
	this->vbos.push_back(vbo);
	this->vbos.push_back(ibo);

	rotationSpeed = glm::vec3(0.0, 90.0, 0.0);
	rotation = glm::vec3(30.0, 0.0, 0.0);
}

void Cube::update() {
	rotation = 0.01f * rotationSpeed + rotation;
	rotationSin = glm::vec3(rotation.x * M_PI / 180, rotation.y * M_PI / 180, rotation.z * M_PI / 180);}

void Cube::draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix) {
	glUseProgram(program);
	glBindVertexArray(vao);

	// Activate, bind and transform texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->getTexture("cubeTexture"));
	GLuint textureLocation = glGetUniformLocation(program, "texture1");
	glUniform1i(textureLocation, 0);

	// Apply cube rotation, view and projection transformations
	glUniform3f(glGetUniformLocation(program, "rotation"), rotationSin.x, rotationSin.y, rotationSin.z);
	glUniformMatrix4fv(glGetUniformLocation(program, "viewMatrix"), 1, false, &viewMatrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "projectionMatrix"), 1, false, &projectionMatrix[0][0]);

	// Draw
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}
