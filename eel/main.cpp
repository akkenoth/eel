#include <iostream>

#include "Engine/Engine.h"
#include "Models/Cube.h"
#include "Models/Sphere.h"

#ifdef _WIN32
#define DIR_SEP '\\'
#else
#define DIR_SEP '/'
#endif

int main(int argc, char** argv) {
	Engine* engine = new Engine();
	if(!engine->init()) {
		std::cout << "Engine initialization failed\n";
		return 1;
	}
	engine->getShaderManager()->createProgram("colorShader", "Shaders/VertexShader.glsl", "Shaders/FragmentShader.glsl");
	
	GLuint program = engine->getShaderManager()->getProgram("colorShader");
	if(program == 0) {
		std::cout << "Program initialization failed\n";
		return 2;
	}

	Sphere* sphere = new Sphere();
	sphere->setProgram(program);
	sphere->create(1.0, 24, 48);
	sphere->setTexture("sphereTexture0", engine->getTextureLoader()->loadTexture("Resources/Textures/sphere1.bmp", 256, 256));
	sphere->setTexture("sphereTexture1", engine->getTextureLoader()->loadTexture("Resources/Textures/sphere_dots.png", 256, 256));
	engine->getModelManager()->setModel("sphere", sphere);

	engine->run();

	delete engine;
	return 0;
}
