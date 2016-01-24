#include "SceneManager.h"

SceneManager::SceneManager() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	camera = new Camera(glm::vec3(0.0f, 0.0f, 5.0f));
	for(LightSource* l : lights) {
		l = NULL;
	}

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
	glm::mat4 projectionMatrix = glm::perspective(camera->verticalFOV, camera->aspectRatio, camera->nearClip, camera->farClip);
	// Todo: replace lookAt
	glm::mat4 viewMatrix = glm::lookAt(camera->position, glm::vec3(0,0,0), camera->orientation);
	glUniformMatrix4fv(glGetUniformLocation(program, "viewMatrix"), 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "projectionMatrix"), 1, GL_FALSE, &projectionMatrix[0][0]);
	glUniform3f(glGetUniformLocation(program, "eyePosition"), camera->position.x, camera->position.y, camera->position.z);

	// Set up lights
	std::vector<glm::mat3> lightMatrices;
	lightMatrices.reserve(MAX_LIGHTS);
	std::vector<GLint> lightIsPointLight;
	for(auto const& l : lights) {
		if(l == NULL || !l->enabled) {
			continue;
		}

		glm::mat3 lightMatrix(l->position, l->color, glm::vec3(l->attenuationConstant, l->attenuationLinear, l->attenuationQuadratic));
		lightMatrices.push_back(lightMatrix);
		lightIsPointLight.push_back((GLint)(l->isPointLight));
	}

	glUniformMatrix3fv(glGetUniformLocation(program, "lights"), MAX_LIGHTS/*lightMatrices.size()*/, GL_FALSE, glm::value_ptr(lightMatrices[0]));
	glUniform1iv(glGetUniformLocation(program, "lightIsPointlight"), MAX_LIGHTS/*lightIsPointLight.size()*/, &lightIsPointLight[0]);
	glUniform1i(glGetUniformLocation(program, "lightCount"), lightMatrices.size());

	/*for(int i = 0; i < MAX_LIGHTS; i++) {
		LightSource* l = lights[i];
		if(l == NULL || !l->enabled) {
			continue;
		}

		std::string lightUniformString = std::string("light") + std::to_string(i);
		glm::mat3 lightMatrix(l->position, l->color, glm::vec3(l->attenuationConstant, l->attenuationLinear, l->attenuationQuadratic));
		glUniformMatrix3fv(glGetUniformLocation(program, lightUniformString.c_str()), 1, GL_FALSE, &lightMatrix[0][0]);
		lightUniformString = std::string("light") + std::to_string(i) + "PointLight";
		glUniform1i(glGetUniformLocation(program, lightUniformString.c_str()), l->isPointLight);
	}*/

	// Draw models
	modelManager->draw(program);
}

void SceneManager::notifyFrameEnd() {}

void SceneManager::notifyReshape(int width, int height, int previousWidth, int previousHeight) {
	camera->aspectRatio = (float)(width) / (float)(height);
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

void SceneManager::addLight(unsigned int index, const glm::vec3& p, const glm::vec3& c, const float& aC, const float& aL, const float& aQ, const bool& iPL) {
	if(index > lights.size() || lights.size() >= MAX_LIGHTS) {
		return;
	}

	LightSource* light = new LightSource(p, c, aC, aL, aQ, iPL);
	lights.insert(lights.begin() + index, light);
}

LightSource* SceneManager::getLight(unsigned int index) {
	if(index >= lights.size()) {
		return NULL;
	}
	return lights[index];
}

void SceneManager::clearLight(unsigned int index) {
	if(index >= lights.size()) {
		return;
	}
	lights.erase(lights.begin() + index);
}
