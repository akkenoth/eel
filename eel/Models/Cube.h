#ifndef _MODELS_CUBE_H
#define _MODELS_CUBE_H

#include <time.h>
#include "RenderModel.h"

class Cube : public RenderModel {
private:
	glm::vec3 rotation;
	glm::vec3 rotationSpeed;
	glm::vec3 rotationSin;
	time_t timer;
public:
	Cube();
	~Cube();

	void create();
	virtual void update(const float totalTimePassed = 0.0f, const float deltaTime = 0.0f) override final;
	virtual void draw(const GLuint program) override final;
};

#endif // !_MODELS_CUBE_H
