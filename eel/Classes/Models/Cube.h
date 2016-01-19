#pragma once

#include <time.h>
#include "../RenderModel.h"

class Cube : RenderModel {
private:
	glm::vec3 rotation;
	glm::vec3 rotationSpeed;
	time_t timer;
public:
	Cube();
	~Cube();

	void create();
	virtual void update() override final;
	virtual void draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix) override final;
};
