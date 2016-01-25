#include "Engine.h"

WindowInfo* Engine::window;
GLUTListener* Engine::listener;

Engine::Engine() {}

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

	glutIdleFunc(idleCallback);
	glutDisplayFunc(displayCallback);
	glutReshapeFunc(reshapeCallback);
	glutCloseFunc(closeCallback);

	initGLEW();

	glDebugMessageCallback(DebugOutput::printDebugOutput, NULL);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	std::cout << "Info | Vendor: " << glGetString(GL_VENDOR) << " | Renderer: " << glGetString(GL_RENDERER) << " | OpenGl version: " << glGetString(GL_VERSION) << std::endl;
}

void Engine::idleCallback() {
	glutPostRedisplay();
}

void Engine::displayCallback() {
	if(!listener) {
		return;
	}

	listener->notifyFrameBegin();
	listener->notifyFrameDisplay();
	glutSwapBuffers();
	listener->notifyFrameEnd();
}

void Engine::reshapeCallback(int width, int height) {
	if(!window->isReshapable) {
		return;
	}

	if(listener) {
		listener->notifyReshape(width, height, window->width, window->height);
	}
	window->width = width;
	window->height = height;
	glViewport(0, 0, width, height);
}

void Engine::closeCallback() {
	glutLeaveMainLoop();
}

bool Engine::init() {
	window = new WindowInfo(std::string("EEL"), 200, 200, 800, 800, true);
	///TODO: make compatible with CORE.
	context = new ContextInfo(3, 3, true /*CORE*/);
	framebuffer = new FramebufferInfo(true, true, true, true);

	initGLUT();
	sceneManager = new SceneManager();
	listener = sceneManager;
	shaderManager = new ShaderManager();
	modelManager = new ModelManager();
	textureLoader = new TextureLoader();
	if(sceneManager && shaderManager && modelManager && textureLoader) {
		sceneManager->setModelManager(modelManager);
	} else {
		return false;
	}

	return true;
}

void Engine::run() {
	glutMainLoop();
}

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

void Engine::enterFullscreen() {
	glutFullScreen();
}

void Engine::exitFullscreen() {
	glutLeaveFullScreen();
}
