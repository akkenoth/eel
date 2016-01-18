#pragma once

#include "ShaderManager.h"
#include "../Interfaces/GLUTListener.h"

class SceneManager : public GLUTListener {
private:
	ShaderManager* shaderManager;
public:
	SceneManager();
	~SceneManager();

	virtual void notifyFrameBegin();
	virtual void notifyFrameDisplay();
	virtual void notifyFrameEnd();
	virtual void notifyReshape(int width, int height, int previousWidth, int previousHeight);
};

