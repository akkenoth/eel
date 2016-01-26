#include <iostream>

#include "Engine/Engine.h"
#include "Models/Sphere.h"
#include "Models/Skybox.h"
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

	glm::vec3 sunPosition(9.0f, 20.0f, -12.0f);

	engine->getSceneManager()->addLight(0, sunPosition, glm::vec3(1.0), 1.0f, 0.003f, 0.0001f);
	engine->getSceneManager()->addLight(0, glm::vec3(3.0f, -5.0f, 0.0f), glm::vec3(4.0f, 1.0f, 1.0f), 1.0f, 0.03f, 0.005f);

	Skybox* skybox = new Skybox();
	skybox->create(40.0f);
	skybox->addMaterial(0, "Resources/Skybox/skybox1.bmp", 1.0f, 0.0f, 0.0f, 0.0f, engine->getTextureLoader());
	engine->getModelManager()->setModel("skybox", skybox);

	Sphere* sun = new Sphere();
	sun->create(1.5f, 16, 16, glm::vec4(1.0f, 1.0f, 0.9f, 1.0f));
	sun->setBaseMaterial(1.0f, 0.0f, 0.0f, 0.0f);
	sun->setPosition(sunPosition);
	engine->getModelManager()->setModel("sun", sun);

	Sphere* sphere = new Sphere();
	sphere->create(1.0f, 24, 48);
	sphere->setRotation(glm::vec3(30.0f, 0.0f, 0.0f));
	sphere->setRotationSpeed(glm::vec3(0.0f, 20.0f, 0.0f));
	sphere->addMaterial(0, "Resources/Textures/sphere1.bmp", 0.02f, 0.3f, 2.5f, 15.0f, engine->getTextureLoader());
	sphere->addMaterial(1, "Resources/Textures/sphere_dots.png", 0.02f, 0.8f, 1.0f, 1.0f, engine->getTextureLoader());
	sphere->addNormalMap("Resources/Textures/fish-normal.bmp", engine->getTextureLoader());
	engine->getModelManager()->setModel("sphere", sphere);
	
	engine->run();

	delete engine;
	return 0;
}
