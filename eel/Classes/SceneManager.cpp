#include "SceneManager.h"

SceneManager::SceneManager() {
	glEnable(GL_DEPTH_TEST);

	viewMatrix = glm::mat4(1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, -1.0f, 0.0f,
		0.0f, 0.0f, 10.0f, 1.0f);

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
	modelManager->draw(projectionMatrix, viewMatrix);
}

void SceneManager::notifyFrameEnd() {}

void SceneManager::notifyReshape(int width, int height, int previousWidth, int previousHeight) {
	GLfloat aspectRatio = (GLfloat) (glutGet(GLUT_WINDOW_WIDTH)) / (GLfloat) (glutGet(GLUT_WINDOW_HEIGHT));
	///TODO: make configurable
	GLfloat angle = 45.0f;
	GLfloat nearClip = 0.1f;
	GLfloat farClip = 1000.0f;
	projectionMatrix = glm::mat4(0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f, 0.0f);
	projectionMatrix[0][0] = 1.0f / (aspectRatio*tan(angle / 2.0f));
	projectionMatrix[1][1] = 1.0f / tan(angle / 2.0f);
	projectionMatrix[2][2] = (-nearClip - farClip) / (nearClip - farClip);
	projectionMatrix[3][2] = 2.0f * nearClip * farClip / (nearClip - farClip);
}

ModelManager* SceneManager::getModelManager() {
	return modelManager;
}
