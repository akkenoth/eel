#pragma once

#include <iostream>
#include "../Libs/glew/glew.h"
#include "../Libs/freeglut/freeglut.h"
#include "../Structures/ContextInfo.h"
#include "../Structures/FramebufferInfo.h"
#include "../Structures/WindowInfo.h"
#include "../Interfaces/GLUTListener.h"
#include "DebugOutput.h"
#include "ModelManager.h"
#include "SceneManager.h"
#include "ShaderManager.h"

class Engine {
private:
	ModelManager* modelManager;
	SceneManager* sceneManager;
	ShaderManager* shaderManager;

	static WindowInfo* window;
	FramebufferInfo* framebuffer;
	ContextInfo* context;
	
	void initGLEW();
	void initGLUT();

	static GLUTListener* listener;
	static void idleCallback();
	static void displayCallback();
	static void reshapeCallback(int width, int height);
	static void closeCallback();
public:
	Engine();
	~Engine();
	bool init();
	void run();

	ModelManager* getModelManager() const;
	SceneManager* getSceneManager() const;
	ShaderManager* getShaderManager() const;

	void enterFullscreen();
	void exitFullscreen();
};
