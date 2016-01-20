#pragma once

#include "ShaderManager.h"
#include "../Models/Triangle.h"
#include "../Models/Tetragon.h"

class ModelManager {
private:
	std::map<std::string, RenderObject*> modelList;
	std::map<std::string, RenderObject*> modelListNDC;
public:
	ModelManager();
	~ModelManager();

	void draw();
	void draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix);
	void update();
	void deleteModel(const std::string& modelName);
	void deleteNDCModel(const std::string& modelName);
	const RenderObject& getModel(const std::string& modelName);
	const RenderObject& getNDCModel(const std::string& modelName);
	void setModel(const std::string& modelName, RenderObject* modelObject);
};

