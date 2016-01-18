#include "RenderModel.h"

RenderModel::RenderModel() {}

RenderModel::~RenderModel() {
	destroy();
}

void RenderModel::draw() {}

void RenderModel::update() {}

void RenderModel::destroy() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(vbos.size(), &vbos[0]);
	vbos.clear();
}

void RenderModel::setProgram(GLuint program) {
	this->program = program;
}

GLuint RenderModel::getVao() const {
	return vao;
}

const std::vector<GLuint>& RenderModel::getVbos() const {
	return vbos;
}
