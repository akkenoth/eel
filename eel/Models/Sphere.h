#ifndef _MODELS_SPHERE_H
#define _MODELS_SPHERE_H

#include "RenderModel.h"

class Sphere : public RenderModel {
private:
	unsigned int indicesCount;
public:
	Sphere();
	~Sphere();

	void create(GLfloat radius, GLuint rings, GLuint sectors, const glm::vec4& color = glm::vec4(0.0f));
	virtual void update(const float totalTimePassed = 0.0f, const float deltaTime = 0.0f) override final;
	virtual void draw(const GLuint program) override final;
};

#endif // !_MODELS_SPHERE_H
