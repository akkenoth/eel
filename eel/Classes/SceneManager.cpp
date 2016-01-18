#include "SceneManager.h"

SceneManager::SceneManager() {
	glEnable(GL_DEPTH_TEST);

	shaderManager = new ShaderManager();
	shaderManager->createProgram("simpleColorShader", "Shaders\\VertexShader.glsl", "Shaders\\FragmentShader.glsl");

	modelManager = new ModelManager();
}

SceneManager::~SceneManager() {
	delete shaderManager;
	delete modelManager;
}

void SceneManager::notifyFrameBegin() {
	modelManager->update();
}

void SceneManager::notifyFrameDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	modelManager->draw();
}

void SceneManager::notifyFrameEnd() {}

void SceneManager::notifyReshape(int width, int height, int previousWidth, int previousHeight) {}
