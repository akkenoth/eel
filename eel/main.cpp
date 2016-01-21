#include <iostream>

#include "Engine/Engine.h"
#include "Models/Cube.h"
#include "Models/Sphere.h"
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

	/*Cube* cube = new Cube();
	cube->setProgram(program);
	cube->create();

	GLuint texture = SOIL_load_OGL_texture("Resources\\Textures\\test512.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	if(texture == 0) {
		std::cout << "Texture loading failed\n";
		return 3;
	}
	cube->setTexture("cubeTexture", texture);
	engine->getModelManager()->setModel("cube", cube);*/

	Sphere* sphere = new Sphere();
	sphere->setProgram(program);
	sphere->create(1.0, 24, 48);
	sphere->setTexture("sphereTexture0", SOIL_load_OGL_texture("Resources\\Textures\\sphere1.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_TEXTURE_REPEATS));
	sphere->setTexture("sphereTexture1", SOIL_load_OGL_texture("Resources\\Textures\\sphere2.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_TEXTURE_REPEATS));
	sphere->setTexture("sphereTexture1Alpha", SOIL_load_OGL_texture("Resources\\Textures\\sphere_alpha.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_TEXTURE_REPEATS));
	engine->getModelManager()->setModel("sphere", sphere);

	engine->run();

	delete engine;
	return 0;
}
