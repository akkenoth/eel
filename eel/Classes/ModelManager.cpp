#include "ModelManager.h"

ModelManager::ModelManager() {
	Triangle* t3 = new Triangle();
	t3->setProgram(ShaderManager::getProgram("simpleColorShader"));
	t3->create();
	modelList["triangle1"] = t3;

	Tetragon* t4 = new Tetragon();
	t4->setProgram(ShaderManager::getProgram("simpleColorShader"));
	t4->create();
	modelList["tetragon1"] = t4;
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
