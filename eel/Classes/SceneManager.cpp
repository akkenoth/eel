#include "SceneManager.h"

SceneManager::SceneManager() {
	glEnable(GL_DEPTH_TEST);

	shaderManager = new ShaderManager();
	shaderManager->createProgram("simpleColorShader", "Shaders\\VertexShader.glsl", "Shaders\\FragmentShader.glsl");
}

SceneManager::~SceneManager() {
	delete shaderManager;
}

void SceneManager::notifyFrameBegin() {}

void SceneManager::notifyFrameDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
}

void SceneManager::notifyFrameEnd() {}

void SceneManager::notifyReshape(int width, int height, int previousWidth, int previousHeight) {}
