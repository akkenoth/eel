#include "Initializer.h"

GLUTListener* Initializer::listener;
WindowInfo Initializer::windowInfo;

void Initializer::initGLEW() {
	glewExperimental = true;
	if(glewInit() == GLEW_OK) {
		std::cout << "GLEW initialized\n";
	}

	if(glewIsSupported("GL_VERSION_4_1")) {
		std::cout << "GLEW GL 4.1 supported.\n";
	} else {
		std::cout << "GLEW GL 4.1 NOT supported.\n";
	}
}

void Initializer::initGLUT(const WindowInfo& w, const ContextInfo& c, const FramebufferInfo& f) {
	int argc = 1;
	char *argv[] = {"foobar", NULL};
	initGLUT(w, c, f, argc, argv);
}

void Initializer::initGLUT(const WindowInfo& w, const ContextInfo& c, const FramebufferInfo& f, int argc, char** argv) {
	glutInit(&argc, argv);

	if(c.core) {
		glutInitContextVersion(c.majorVersion, c.minorVersion);
		glutInitContextProfile(GLUT_CORE_PROFILE);
	} else {
		glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	}

	glutInitDisplayMode(f.flags);
	glutInitWindowPosition(w.positionX, w.positionY);
	glutInitWindowSize(w.width, w.height);
	glutCreateWindow(w.name.c_str());

	std::cout << "GLUT initialized\n";

	glutIdleFunc(idleCallback);
	glutDisplayFunc(displayCallback);
	glutReshapeFunc(reshapeCallback);
	glutCloseFunc(closeCallback);

	initGLEW();

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	windowInfo = w;
	printOpenGLInfo(w, c);
}

void Initializer::run() {
	glutMainLoop();
}

void Initializer::close() {
	glutLeaveMainLoop();
}

void Initializer::printOpenGLInfo(const WindowInfo& w, const ContextInfo& c) {
	std::cout << "Info | Vendor: " << glGetString(GL_VENDOR) << " | Renderer: " << glGetString(GL_RENDERER) << " | OpenGl version: " << glGetString(GL_VERSION) << std::endl;
}

void Initializer::setListener(GLUTListener*& l) {
	listener = l;
}

void Initializer::enterFullscreen() {
	glutFullScreen();
}

void Initializer::exitFullscreen() {
	glutLeaveFullScreen();
}

void Initializer::idleCallback() {
	glutPostRedisplay();
}

void Initializer::displayCallback() {
	if(!listener) {
		return;
	}

	listener->notifyFrameBegin();
	listener->notifyFrameDisplay();
	glutSwapBuffers();
	listener->notifyFrameEnd();
}

void Initializer::reshapeCallback(int width, int height) {
	if(!windowInfo.isReshapable) {
		return;
	}

	if(listener) {
		listener->notifyReshape(width, height, windowInfo.width, windowInfo.height);
	}

	windowInfo.width = width;
	windowInfo.height = height;
}

void Initializer::closeCallback() {
	close();
}
