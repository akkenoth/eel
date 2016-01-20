#ifndef _ENGINE_SCENEMANAGER_H
#define _ENGINE_SCENEMANAGER_H

#include "ShaderManager.h"
#include "ModelManager.h"
#include "../Interfaces/GLUTListener.h"

class SceneManager : public GLUTListener {
private:
	ModelManager* modelManager;
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;

public:
	SceneManager();
	~SceneManager();

	virtual void notifyFrameBegin() override;
	virtual void notifyFrameDisplay() override;
	virtual void notifyFrameEnd() override;
	virtual void notifyReshape(int width, int height, int previousWidth, int previousHeight) override;

	void setModelManager(ModelManager*& manager);
};

#endif // !_ENGINE_SCENEMANAGER_H
