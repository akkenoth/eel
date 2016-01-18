#pragma once

#include "ShaderManager.h"
#include "Triangle.h"
#include "Tetragon.h"

class ModelManager {
private:
	std::map<std::string, RenderObject*> modelList;
public:
	ModelManager();
	~ModelManager();

	void draw();
	void update();
	void deleteModel(const std::string& modelName);
	const RenderObject& getModel(const std::string& modelName);
};

