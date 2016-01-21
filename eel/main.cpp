#include <iostream>

#include "Engine/Engine.h"
#include "Models/Cube.h"
#include "Libs/soil/SOIL.h"

int main(int argc, char** argv) {
	Engine* engine = new Engine();
	if(!engine->init()) {
		std::cout << "Engine initialization failed\n";
		return 1;
	}
	engine->getShaderManager()->createProgram("colorShader", "Shaders\\VertexTextureShader.glsl", "Shaders\\FragmentTextureShader.glsl");
	GLuint program = engine->getShaderManager()->getProgram("colorShader");
	if(program == 0) {
		std::cout << "Program initialization failed\n";
		return 2;
	}

	Cube* cube = new Cube();
	cube->setProgram(program);
	cube->create();

	GLuint texture = SOIL_load_OGL_texture("Resources\\Textures\\test512.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	if(texture == 0) {
		std::cout << "Texture loading failed\n";
		return 3;
	}

	cube->setTexture("cubeTexture", texture);
	engine->getModelManager()->setModel("cube", cube);

	engine->run();

	delete engine;
	return 0;
}
