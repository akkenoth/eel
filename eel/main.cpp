#include <iostream>

#include "Engine/Engine.h"
#include "Models/Cube.h"

int main(int argc, char** argv) {
	Engine* engine = new Engine();
	engine->init();
	engine->getShaderManager()->createProgram("colorShader", "Shaders\\VertexShader.glsl", "Shaders\\FragmentShader.glsl");

	Cube* cube = new Cube();
	cube->setProgram(engine->getShaderManager()->getProgram("colorShader"));
	cube->create();
	engine->getModelManager()->setModel("cube", cube);

	engine->run();

	delete engine;
	return 0;
}
