#ifndef _MODELS_CUBOID_H
#define _MODELS_CUBOID_H

#include <time.h>
#include "RenderModel.h"

class Cuboid : public RenderModel {
private:
	glm::vec3 rotation;
	glm::vec3 rotationSpeed;
	glm::vec3 rotationSin;
	time_t timer;
public:
	Cuboid();
	~Cuboid();

	void create(GLfloat sizeX, GLfloat sizeY, GLfloat sizeZ, const glm::vec4& color = glm::vec4(0.0f));
	virtual void update(const float totalTimePassed = 0.0f, const float deltaTime = 0.0f) override final;
	virtual void draw(const GLuint program) override final;
};

#endif // !_MODELS_CUBOID_H
