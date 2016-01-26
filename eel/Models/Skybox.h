#ifndef _MODELS_SKYBOX_H
#define _MODELS_SKYBOX_H

#include "RenderModel.h"

class Skybox : public RenderModel {
private:
public:
	Skybox();
	~Skybox();

	void create(GLfloat size);
	virtual void update(const float totalTimePassed = 0.0f, const float deltaTime = 0.0f) override final;
	virtual void draw(const GLuint program) override final;
};

#endif // !_MODELS_SKYBOX_H
