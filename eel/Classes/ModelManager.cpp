#include "ModelManager.h"

ModelManager::ModelManager() {
	Triangle* t = new Triangle();
	t->setProgram(ShaderManager::getProgram("simpleColorShader"));
	t->create();
	modelList["triangle1"] = t;
}

ModelManager::~ModelManager() {
	for(auto model : modelList) {
		delete model.second;
	}
	modelList.clear();
}

void ModelManager::draw() {
	for(auto model : modelList) {
		model.second->draw();
	}
}

void ModelManager::update() {
	for(auto model : modelList) {
		model.second->update();
	}
}

void ModelManager::deleteModel(const std::string& modelName) {
	std::map<std::string, RenderObject*>::iterator it;
	it = modelList.find(modelName);
	if(it == modelList.end()) {
		return;
	}

	it->second->destroy();
	modelList.erase(it);
}

const RenderObject& ModelManager::getModel(const std::string & modelName) {
	return (*modelList.at(modelName));
}
