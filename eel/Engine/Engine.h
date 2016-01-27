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
#include "InputManager.h"

class Engine {
private:
	ModelManager* modelManager;
	SceneManager* sceneManager;
	ShaderManager* shaderManager;
	TextureLoader* textureLoader;
	GLUTListener* listener;

	WindowInfo* window;
	FramebufferInfo* framebuffer;
	ContextInfo* context;

	InputManager* inputManager;
	bool isFullscreen;
	
	void initGLEW();
	void initGLUT();

	static void idleCallback();
	static void displayCallback();
	static void reshapeCallback(int width, int height);
	static void closeCallback();
	static void handleKeyboardCallback(unsigned char key, int x, int y);
	static void handleKeyboardUpCallback(unsigned char key, int x, int y);
	static void handleKeyboardSpecialCallback(int key, int x, int y);
	static void handleKeyboardSpecialUpCallback(int key, int x, int y);
	static void handleMouseMovement(int x, int y);
public:
	Engine();
	~Engine();
	bool init();
	void run();
	void toggleFullscreen();

	ModelManager* getModelManager() const;
	SceneManager* getSceneManager() const;
	ShaderManager* getShaderManager() const;
	TextureLoader* getTextureLoader() const;
	GLUTListener* getListener() const;
	WindowInfo* getWindowInfo() const;
	InputManager* getInputManager() const;
};

#endif // !_ENGINE_ENGINE_H
