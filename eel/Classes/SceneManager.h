#pragma once

#include "ShaderManager.h"
#include "ModelManager.h"
#include "../Interfaces/GLUTListener.h"

class SceneManager : public GLUTListener {
private:
	ShaderManager* shaderManager;
	ModelManager* modelManager;
public:
	SceneManager();
	~SceneManager();

	virtual void notifyFrameBegin() override;
	virtual void notifyFrameDisplay() override;
	virtual void notifyFrameEnd() override;
	virtual void notifyReshape(int width, int height, int previousWidth, int previousHeight) override;
};

