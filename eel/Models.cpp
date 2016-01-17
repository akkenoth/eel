#include "Models.h"

Models::Models() {}
Models::~Models() {
	for(std::map<std::string, Model>::iterator it = modelList.begin(); it != modelList.end(); ++it) {
		GLuint* p = &it->second.vao;
		glDeleteVertexArrays(1, p);
		glDeleteBuffers(it->second.vbos.size(), &it->second.vbos[0]);
		it->second.vbos.clear();
	}
	modelList.clear();
}

void Models::createTriangleModel(const std::string& modelName) {
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	std::vector<VertexFormat> vertices;
	vertices.push_back(VertexFormat(glm::vec3(-0.25, -0.25, 0.0), glm::vec4(1, 0, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(0.25, -0.25, 0.0), glm::vec4(0, 1, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(0.0, 0.25, 0.0), glm::vec4(0, 0, 1, 1)));
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat)*3, &vertices[0], GL_STATIC_DRAW);
	// Qualifier (pipe) 0 - positions
	glEnableVertexAttribArray(0);
	// pipe 0, 3 values, floats, not normalized, offset between next items in array, offset from beggining of item
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::position)));
	// Q 1 - colors
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::color)));

	Model testTriangle;
	testTriangle.vao = vao;
	testTriangle.vbos.push_back(vbo);
	modelList[modelName] = testTriangle;
}

void Models::deleteModel(const std::string& modelName) {
	Model m = modelList[modelName];
	GLuint p = m.vao;
	glDeleteVertexArrays(1, &p);
	glDeleteBuffers(m.vbos.size(), &m.vbos[0]);
	m.vbos.clear();
	modelList.erase(modelName);
}

GLuint Models::getModel(const std::string& modelName) {
	return modelList[modelName].vao;
}