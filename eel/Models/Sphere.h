#ifndef _MODELS_SPHERE_H
#define _MODELS_SPHERE_H

#include "RenderModel.h"

class Sphere : public RenderModel {
private:
	std::chrono::time_point<std::chrono::steady_clock> spawnTime;
	float timePassed;
	glm::vec3 baseRotation;
	glm::vec3 rotation;
	glm::vec3 rotationSpeed;
	glm::vec3 rotationSin;
	unsigned int indicesCount;
public:
	Sphere();
	~Sphere();

	void create(GLfloat radius, GLuint rings, GLuint sectors);
	virtual void update() override final;
	virtual void draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix) override final;
};

#endif // !_MODELS_SPHERE_H
