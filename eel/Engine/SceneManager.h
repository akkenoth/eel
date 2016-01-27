#ifndef _ENGINE_SCENEMANAGER_H
#define _ENGINE_SCENEMANAGER_H

#include <chrono>
#include "../Interfaces/GLUTListener.h"
#include "ModelManager.h"
#include "InputManager.h"
#include "Camera.h"
#include "../Structures/LightSource.h"
#include "../Libs/glm/gtc/type_ptr.hpp"

#define MAX_LIGHTS 4

class SceneManager : public GLUTListener {
private:
	GLuint program;
	ModelManager* modelManager;
	InputManager* inputManager;
	std::vector<LightSource*> lights;
	Camera* camera;
	std::chrono::time_point<std::chrono::steady_clock> spawnTime;
	std::chrono::time_point<std::chrono::steady_clock> lastTick;
	float totalTimePassed;
public:
	SceneManager();
	~SceneManager();

	virtual void notifyFrameBegin() override;
	virtual void notifyFrameDisplay() override;
	virtual void notifyFrameEnd() override;
	virtual void notifyReshape(int width, int height, int previousWidth, int previousHeight) override;

	void setProgram(GLuint program);
	void setModelManager(ModelManager*& manager);
	void setInputManager(InputManager*& manager);
	void addLight(unsigned int index, const glm::vec3& position, const glm::vec3& color = glm::vec3(1.0f), const float& attenuationConstant = 1.0f, const float& attenuationLinear = 0.0f, const float& attenuationQuadratic = 0.0f, const bool& isPointLight = true);
	void clearLight(unsigned int index);
	LightSource* getLight(unsigned int index) const;
	Camera* getCamera() const;

	void toggleAnimation();
};

#endif // !_ENGINE_SCENEMANAGER_H
