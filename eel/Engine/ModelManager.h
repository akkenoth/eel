#ifndef _ENGINE_MODELMANAGER_H
#define _ENGINE_MODELMANAGER_H

#include "../Libs/glm/gtc/matrix_transform.hpp"
#include "ShaderManager.h"
#include "../Interfaces/RenderObject.h"

class ModelManager {
private:
	std::map<std::string, RenderObject*> modelList;
	std::map<std::string, RenderObject*> modelListNDC;
public:
	ModelManager();
	~ModelManager();

	void draw(const GLuint program);
	void update(const float totalTimePassed, const float deltaTime);
	void deleteModel(const std::string& modelName);
	void deleteNDCModel(const std::string& modelName);
	const RenderObject& getModel(const std::string& modelName);
	const RenderObject& getNDCModel(const std::string& modelName);
	void setModel(const std::string& modelName, RenderObject* modelObject);
};

#endif // !_ENGINE_MODELMANAGER_H
