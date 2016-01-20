#ifndef _ENGINE_ENGINE_H
#define _ENGINE_ENGINE_H

#include "DebugOutput.h" // This includes GL and iostream
#include "../Structures/ContextInfo.h"
#include "../Structures/FramebufferInfo.h"
#include "../Structures/WindowInfo.h"
#include "../Interfaces/GLUTListener.h"
#include "ModelManager.h"
#include "SceneManager.h"
#include "ShaderManager.h"
#include "TextureLoader.h"

class Engine {
private:
	ModelManager* modelManager;
	SceneManager* sceneManager;
	ShaderManager* shaderManager;
	TextureLoader* textureLoader;

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
	TextureLoader* getTextureLoader() const;

	void enterFullscreen();
	void exitFullscreen();
};

#endif // !_ENGINE_ENGINE_H
