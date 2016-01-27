#include "SceneManager.h"

SceneManager::SceneManager() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	camera = new Camera(glm::vec3(0.0f, 0.0f, 8.0f));
	spawnTime = std::chrono::steady_clock::now();
}

SceneManager::~SceneManager() {
	delete camera;
	lights.clear();
}

void SceneManager::notifyFrameBegin() {
	std::chrono::time_point<std::chrono::steady_clock> nowTime = std::chrono::steady_clock::now();
	std::chrono::duration<float> fromSpawn = nowTime - spawnTime;
	std::chrono::duration<float> tickDuration = nowTime - lastTick;
	float totalTimePassed = fromSpawn.count();
	float deltaTime = tickDuration.count();
	lastTick = nowTime;

	modelManager->update(totalTimePassed, deltaTime);

	camera->move(deltaTime, inputManager->getKeyState('w'), inputManager->getKeyState('s'), inputManager->getKeyState('a'), inputManager->getKeyState('d'));
	camera->rotate(deltaTime, inputManager->getMouseMovementX(), inputManager->getMouseMovementY());
	inputManager->clearMouseMovement();
}

void SceneManager::notifyFrameDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	///TODO: remove clearcolor
	glClearColor(0.0f, 0.2f, 0.3f, 1.0f);

	// Choose program (shaders)
	glUseProgram(program);

	// Set up time
	glUniform1f(glGetUniformLocation(program, "timePassed"), totalTimePassed);

	// Set up camera
	glm::vec3 eyePosition = camera->getEyePosition();
	glm::mat4 viewMatrix = camera->getViewMatrix();
	glm::mat4 projectionMatrix = camera->getProjectionMatrix();
	glUniform3f(glGetUniformLocation(program, "eyePosition"), eyePosition.x, eyePosition.y, eyePosition.z);
	glUniformMatrix4fv(glGetUniformLocation(program, "viewMatrix"), 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "projectionMatrix"), 1, GL_FALSE, &projectionMatrix[0][0]);

	// Set up lights
	std::vector<glm::mat3> lightMatrices;
	lightMatrices.reserve(MAX_LIGHTS);
	std::vector<GLint> lightIsPointLight;
	lightIsPointLight.reserve(MAX_LIGHTS);
	for(auto const& l : lights) {
		if(l == NULL || !l->enabled) {
			continue;
		}

		glm::mat3 lightMatrix(l->position, l->color, glm::vec3(l->attenuationConstant, l->attenuationLinear, l->attenuationQuadratic));
		lightMatrices.push_back(lightMatrix);
		lightIsPointLight.push_back((GLint)(l->isPointLight));
	}

	int lightCount = lightMatrices.size();
	// If no lights, push at least 1 value to vectors so that &vec[0] is not null-reference
	if(lightCount == 0) {
		lightMatrices.push_back(glm::mat3(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f)));
		lightIsPointLight.push_back(1);
	}
	glUniformMatrix3fv(glGetUniformLocation(program, "lights"), MAX_LIGHTS, GL_FALSE, glm::value_ptr(lightMatrices[0]));
	glUniform1iv(glGetUniformLocation(program, "lightIsPointlight"), MAX_LIGHTS, &lightIsPointLight[0]);
	glUniform1i(glGetUniformLocation(program, "lightCount"), lightCount);

	// Draw models

	glCullFace(GL_FRONT);
	modelManager->draw(program);
}

void SceneManager::notifyFrameEnd() {}

void SceneManager::notifyReshape(int width, int height, int previousWidth, int previousHeight) {
	camera->setAspectRatio((float)(width) / (float)(height));
}

void SceneManager::setProgram(GLuint program) {
	if(program == 0) {
		return;
	}
	this->program = program;
}

void SceneManager::setModelManager(ModelManager *& manager) {
	modelManager = manager;
}

void SceneManager::setInputManager(InputManager*& manager) {
	inputManager = manager;
}

void SceneManager::addLight(unsigned int index, const glm::vec3& p, const glm::vec3& c, const float& aC, const float& aL, const float& aQ, const bool& iPL) {
	if(index > lights.size() || lights.size() >= MAX_LIGHTS) {
		return;
	}

	LightSource* light = new LightSource(p, c, aC, aL, aQ, iPL);
	lights.insert(lights.begin() + index, light);
}

void SceneManager::clearLight(unsigned int index) {
	if(index >= lights.size()) {
		return;
	}
	lights.erase(lights.begin() + index);
}

LightSource* SceneManager::getLight(unsigned int index) const {
	if(index >= lights.size()) {
		return NULL;
	}
	return lights[index];
}

Camera* SceneManager::getCamera() const {
	return camera;
}

void SceneManager::toggleAnimation() {
	modelManager->toggleAnimation(totalTimePassed);
}
