#pragma once

#include <iostream>
#include "../Libs/glew/glew.h"
#include "../Libs/freeglut/freeglut.h"
#include "../Structures/ContextInfo.h"
#include "../Structures/FramebufferInfo.h"
#include "../Structures/WindowInfo.h"
#include "../Interfaces/GLUTListener.h"

class Initializer {
private:
	static GLUTListener* listener;
	static WindowInfo windowInfo;

	static void idleCallback();
	static void displayCallback();
	static void reshapeCallback(int width, int height);
	static void closeCallback();
public:
	static void initGLEW();
	static void initGLUT(const WindowInfo& w, const ContextInfo& c, const FramebufferInfo& f);
	static void initGLUT(const WindowInfo& w, const ContextInfo& c, const FramebufferInfo& f, int argc, char** argv);
	static void run();
	static void close();
	static void printOpenGLInfo(const WindowInfo& w, const ContextInfo& c);
	static void setListener(GLUTListener*& l);
	void enterFullscreen();
	void exitFullscreen();
};
