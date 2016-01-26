#include "Engine.h"

/// Ctor & Dtor
Engine::Engine() {
	isFullscreen = false;
}

Engine::~Engine() {
	if(sceneManager) {
		delete sceneManager;
	}
	if(shaderManager) {
		delete shaderManager;
	}
	if(modelManager) {
		delete modelManager;
	}
	if(window) {
		delete window;
	}
	if(context) {
		delete context;
	}
	if(framebuffer) {
		delete framebuffer;
	}
	if(textureLoader) {
		delete textureLoader;
	}
}

/// Private

void Engine::initGLEW() {
	glewExperimental = true;
	if(glewInit() == GLEW_OK) {
		std::cout << "GLEW initialized\n";
	}

	if(glewIsSupported("GL_VERSION_3_3")) {
		std::cout << "GLEW GL 3.3 supported.\n";
	} else {
		std::cout << "GLEW GL 3.3 NOT supported.\n";
	}
}

void Engine::initGLUT() {
	int argc = 1;
	char *argv[] = {"foobar"};
	glutInit(&argc, argv);

	if(context->core) {
		glutInitContextVersion(context->majorVersion, context->minorVersion);
		glutInitContextProfile(GLUT_CORE_PROFILE);
	} else {
		glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	}

	glutInitDisplayMode(framebuffer->flags);
	glutInitWindowPosition(window->positionX, window->positionY);
	glutInitWindowSize(window->width, window->height);
	// in case GL_DEBUG_OUTPUT doesn't work
	// glutInitContextFlags(GLUT_DEBUG);
	glutCreateWindow(window->name.c_str());

	std::cout << "GLUT initialized\n";
	glEnable(GL_DEBUG_OUTPUT);

	glutSetWindowData(static_cast<void *>(this));

	glutIdleFunc(idleCallback);
	glutDisplayFunc(displayCallback);
	glutReshapeFunc(reshapeCallback);
	glutCloseFunc(closeCallback);

	glutKeyboardFunc(handleKeyboardCallback);
	glutKeyboardUpFunc(handleKeyboardUpCallback);
	glutSpecialFunc(handleKeyboardSpecialCallback);
	glutSpecialUpFunc(handleKeyboardSpecialUpCallback);
	glutMotionFunc(handleMouseMovement);
	glutPassiveMotionFunc(handleMouseMovement);

	initGLEW();

	glDebugMessageCallback(DebugOutput::printDebugOutput, NULL);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	std::cout << "Info | Vendor: " << glGetString(GL_VENDOR) << " | Renderer: " << glGetString(GL_RENDERER) << " | OpenGl version: " << glGetString(GL_VERSION) << std::endl;
}

void Engine::enterFullscreen() {
	glutFullScreen();
	isFullscreen = true;
}

void Engine::exitFullscreen() {
	glutLeaveFullScreen();
	isFullscreen = false;
}

/// Private static

void Engine::idleCallback() {
	Engine* engine = static_cast<Engine*>(glutGetWindowData());
	glutPostRedisplay();
}

void Engine::displayCallback() {
	Engine* engine = static_cast<Engine*>(glutGetWindowData());
	GLUTListener* listener = engine->getListener();
	if(!listener) {
		return;
	}

	listener->notifyFrameBegin();
	listener->notifyFrameDisplay();
	glutSwapBuffers();
	listener->notifyFrameEnd();
}

void Engine::reshapeCallback(int width, int height) {
	Engine* engine = static_cast<Engine*>(glutGetWindowData());
	WindowInfo* window = engine->getWindowInfo();
	if(!window->isReshapable) {
		return;
	}

	GLUTListener* listener = engine->getListener();
	if(listener) {
		listener->notifyReshape(width, height, window->width, window->height);
	}
	window->width = width;
	window->height = height;
	glViewport(0, 0, width, height);
}

void Engine::closeCallback() {
	Engine* engine = static_cast<Engine*>(glutGetWindowData());
	glutLeaveMainLoop();
}

void Engine::handleKeyboardCallback(unsigned char key, int x, int y) {
	Engine* engine = static_cast<Engine*>(glutGetWindowData());
	engine->getInputManager()->setKeyDown(key);
	/*switch(key) {
		default:
			break;
	}*/
}

void Engine::handleKeyboardUpCallback(unsigned char key, int x, int y) {
	Engine* engine = static_cast<Engine*>(glutGetWindowData());
	engine->getInputManager()->setKeyUp(key);
	switch(key) {
		case 27:
			glutLeaveMainLoop();
			return;
		case 'f':
		case 'F':
			engine->toggleFullscreen();
			break;
		case 'm':
		case 'M':
			engine->getInputManager()->toggleMouseCapture();
			break;
	}
}

void Engine::handleKeyboardSpecialCallback(int key, int x, int y) {
	Engine* engine = static_cast<Engine*>(glutGetWindowData());
	SceneManager* sceneManager = engine->getSceneManager();
	switch(key) {
		case GLUT_KEY_UP:
		case GLUT_KEY_DOWN:
		case GLUT_KEY_LEFT:
		case GLUT_KEY_RIGHT:
			//engine->getInputManager()->setSpecialKeyDown(key);
			break;
	}
}

void Engine::handleKeyboardSpecialUpCallback(int key, int x, int y) {
	Engine* engine = static_cast<Engine*>(glutGetWindowData());
	SceneManager* sceneManager = engine->getSceneManager();
	switch(key) {
		case GLUT_KEY_F1:
			if(sceneManager->getLight(0) != NULL) {
				sceneManager->getLight(0)->toggle();
			}
			break;
		case GLUT_KEY_F2:
			if(sceneManager->getLight(1) != NULL) {
				sceneManager->getLight(1)->toggle();
			}
			break;
		case GLUT_KEY_F3:
			if(sceneManager->getLight(2) != NULL) {
				sceneManager->getLight(2)->toggle();
			}
			break;
		case GLUT_KEY_F4:
			if(sceneManager->getLight(3) != NULL) {
				sceneManager->getLight(3)->toggle();
			}
			break;
		case GLUT_KEY_UP:
		case GLUT_KEY_DOWN:
		case GLUT_KEY_LEFT:
		case GLUT_KEY_RIGHT:
			//engine->getInputManager()->setSpecialKeyUp(key);
			break;
	}
}

void Engine::handleMouseMovement(int x, int y) {
	Engine* engine = static_cast<Engine*>(glutGetWindowData());
	engine->getInputManager()->addMouseMovement(x, y);
}

/// Public

bool Engine::init() {
	window = new WindowInfo(std::string("EEL"), 200, 200, 800, 800, true);
	context = new ContextInfo(3, 3, true /*CORE*/);
	framebuffer = new FramebufferInfo(true, true, true, true);

	sceneManager = new SceneManager();
	listener = sceneManager;
	shaderManager = new ShaderManager();
	modelManager = new ModelManager();
	textureLoader = new TextureLoader();
	inputManager = new InputManager();
	if(sceneManager && shaderManager && modelManager && textureLoader && inputManager) {
		sceneManager->setModelManager(modelManager);
		sceneManager->setInputManager(inputManager);
		inputManager->setWindowInfo(window);

		initGLUT();
		//inputManager->toggleMouseCapture();
	} else {
		return false;
	}

	return true;
}

void Engine::run() {
	glutMainLoop();
}

void Engine::toggleFullscreen() {
	if(isFullscreen) {
		exitFullscreen();
	} else {
		enterFullscreen();
	}
}

/// Getters

ModelManager* Engine::getModelManager() const {
	return modelManager;
}

SceneManager* Engine::getSceneManager() const {
	return sceneManager;
}

ShaderManager* Engine::getShaderManager() const {
	return shaderManager;
}

TextureLoader * Engine::getTextureLoader() const {
	return textureLoader;
}

GLUTListener* Engine::getListener() const {
	return listener;
}

WindowInfo* Engine::getWindowInfo() const {
	return window;
}

InputManager* Engine::getInputManager() const {
	return inputManager;
}
