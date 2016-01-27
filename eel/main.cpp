#include <iostream>

#include "Engine/Engine.h"
#include "Models/Sphere.h"
#include "Models/Eel.h"
#include "Models/Cuboid.h"
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

	Skybox* skybox = new Skybox();
	skybox->create(40.0f);
	skybox->addMaterial(0, "Resources/Copyrighted/skybox1.png", 1.0f, 0.0f, 0.0f, 0.0f, engine->getTextureLoader());
	engine->getModelManager()->setModel("skybox", skybox);

	Cuboid* floorBox = new Cuboid();
	floorBox->create(40.0f, 1.0f, 40.0f, glm::vec4(0.24f, 0.267f, 0.337f, 1.0f));
	floorBox->setPosition(glm::vec3(0.0f, -8.0f, 0.0f));
	engine->getModelManager()->setModel("floorBox", floorBox);

	glm::vec3 sunPosition(8.7f, 20.0f, -11.1f);
	engine->getSceneManager()->addLight(0, sunPosition, glm::vec3(1.0), 1.0f, 0.003f, 0.0001f);
	Sphere* sun = new Sphere();
	sun->create(1.2f, 16, 16, glm::vec4(1.0f, 1.0f, 0.9f, 1.0f));
	sun->setBaseMaterial(1.0f, 0.0f, 0.0f, 0.0f);
	sun->setPosition(sunPosition);
	engine->getModelManager()->setModel("sun", sun);

	glm::vec3 lampPosition(10.0f, -1.0f, 10.0f);
	engine->getSceneManager()->addLight(0, lampPosition, glm::vec3(4.0f, 1.0f, 1.0f), 1.0f, 0.003f, 0.0005f);
	Sphere* lamp = new Sphere();
	lamp->create(0.3f, 16, 16, glm::vec4(1.0f, 0.2f, 0.2f, 1.0f));
	lamp->setBaseMaterial(1.0f, 0.0f, 0.0f, 0.0f);
	lamp->setPosition(lampPosition);
	engine->getModelManager()->setModel("lamp", lamp);

	Eel* eel = new Eel();
	eel->create(5.0f, 0.5f, 18);
	eel->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	eel->addMaterial(0, "Resources/Textures/sphere1.bmp", 0.2f, 0.3f, 2.5f, 15.0f, engine->getTextureLoader());
	engine->getModelManager()->setModel("eel", eel);

	Sphere* sphere = new Sphere();
	sphere->create(1.0f, 24, 48);
	sphere->setPosition(glm::vec3(0.0f, -2.0f, 14.0f));
	sphere->setRotation(glm::vec3(30.0f, 0.0f, 0.0f));
	sphere->setRotationSpeed(glm::vec3(0.0f, 20.0f, 0.0f));
	sphere->addMaterial(0, "Resources/Textures/sphere1.bmp", 0.02f, 0.3f, 2.5f, 15.0f, engine->getTextureLoader());
	sphere->addMaterial(1, "Resources/Textures/sphere_dots.png", 0.02f, 0.8f, 1.0f, 1.0f, engine->getTextureLoader());
	sphere->addNormalMap("Resources/Copyrighted/fish-normal.bmp", engine->getTextureLoader());
	engine->getModelManager()->setModel("sphere", sphere);
	
	engine->run();

	delete engine;
	return 0;
}
