#include "ModelManager.h"

ModelManager::ModelManager() {
}

ModelManager::~ModelManager() {
	for(auto model : modelList) {
		delete model.second;
	}
	modelList.clear();
	for(auto model : modelListNDC) {
		delete model.second;
	}
	modelListNDC.clear();
}

void ModelManager::draw(const GLuint program) {
	for(auto model : modelListNDC) {
		model.second->draw();
	}
	for(auto model : modelList) {
		model.second->draw(program);
	}
}

void ModelManager::update(const float totalTimePassed, const float deltaTime) {
	for(auto model : modelList) {
		model.second->update(totalTimePassed, deltaTime);
	}
	for(auto model : modelListNDC) {
		model.second->update(totalTimePassed, deltaTime);
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

void ModelManager::deleteNDCModel(const std::string& modelName) {
	std::map<std::string, RenderObject*>::iterator it;
	it = modelListNDC.find(modelName);
	if(it == modelListNDC.end()) {
		return;
	}

	it->second->destroy();
	modelListNDC.erase(it);
}

const RenderObject& ModelManager::getModel(const std::string& modelName) {
	return (*modelList.at(modelName));
}

const RenderObject & ModelManager::getNDCModel(const std::string& modelName) {
	return (*modelListNDC.at(modelName));
}

void ModelManager::setModel(const std::string& modelName, RenderObject* modelObject) {
	modelList[modelName.c_str()] = modelObject;
}
