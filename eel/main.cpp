#include <iostream>

#include "Engine/Engine.h"
#include "Models/Sphere.h"
#include "Libs/glm/detail/type_vec3.hpp"

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

	engine->getShaderManager()->createProgram("mainShader", "Shaders/VertexShader.glsl", "Shaders/FragmentShader.glsl");
	GLuint program = engine->getShaderManager()->getProgram("mainShader");
	if(program == 0) {
		std::cout << "Program initialization failed\n";
		return 2;
	}
	engine->getSceneManager()->setProgram(program);

	engine->getSceneManager()->addLight(0, glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(1.0), 1.0f, 0.03f, 0.01f);
	engine->getSceneManager()->addLight(0, glm::vec3(3.0f, -5.0f, 0.0f), glm::vec3(4.0f, 1.0f, 1.0f), 1.0f, 0.03f, 0.005f);

	Sphere* sphere = new Sphere();
	sphere->create(1.0, 24, 48);
	sphere->setRotation(glm::vec3(30.0f, 0.0f, 0.0f));
	sphere->setRotationSpeed(glm::vec3(0.0f, 20.0f, 0.0f));
	sphere->addMaterial(0, "Resources/Textures/sphere1.bmp", 0.02f, 0.5f, 1.9f, 10.9f, engine->getTextureLoader());
	sphere->addMaterial(1, "Resources/Textures/sphere_dots.png", 0.02f, 0.5f, 1.9f, 10.9f, engine->getTextureLoader());

	engine->getModelManager()->setModel("sphere", sphere);
	
	engine->run();

	delete engine;
	return 0;
}
