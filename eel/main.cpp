#include <iostream>

#include "Classes/Initializer.h"
#include "Classes/SceneManager.h"

int main(int argc, char** argv) {
	WindowInfo w(std::string("EEL"), 500, 500, 800, 800, true);
	ContextInfo c(4, 3, true);
	FramebufferInfo f(true, true, true, true);
	Initializer::initGLUT(w, c, f, argc, argv);

	GLUTListener* scene = new SceneManager();
	Initializer::setListener(scene);
	Initializer::run();

	delete scene;
	return 0;
}