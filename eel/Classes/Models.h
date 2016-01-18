#pragma once

#include <vector>
#include <map>

#include "../Libs/glew/glew.h"
#include "../Libs/freeglut/freeglut.h"
#include "../Structures/VertexFormat.h"

// Move inside Models?
struct Model {
	// Vertex Array Object
	GLuint vao;
	// Vertex Buffer Objects
	std::vector<GLuint> vbos;

	Model() {}
	~Model() {}
};

class Models {
public:
	Models();
	~Models();
	void createTriangleModel(const std::string& modelName);
	void deleteModel(const std::string& modelName);
	GLuint getModel(const std::string& modelName);
private:
	std::map<std::string, Model> modelList;
};

