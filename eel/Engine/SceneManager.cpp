#include "SceneManager.h"

SceneManager::SceneManager() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Camera position
	viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.5f));
	// World position (?)
	worldMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
}

SceneManager::~SceneManager() {}

void SceneManager::notifyFrameBegin() {
	modelManager->update();
}

void SceneManager::notifyFrameDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.2f, 0.3f, 1.0f);

	modelManager->draw();
	modelManager->draw(projectionMatrix, viewMatrix, worldMatrix);
}

void SceneManager::notifyFrameEnd() {}

void SceneManager::notifyReshape(int width, int height, int previousWidth, int previousHeight) {
	///TODO: make configurable (?)
	GLfloat aspectRatio = (float)(width) / (float)(height);
	GLfloat verticalFOV = 60.0f * (float)(M_PI) / 180.0f;
	GLfloat nearClip = 0.1f;
	GLfloat farClip = 200.0f;
	//glm::lookAt?
	projectionMatrix = glm::perspective(verticalFOV, aspectRatio, nearClip, farClip);
}

void SceneManager::setModelManager(ModelManager *& manager) {
	modelManager = manager;
}
