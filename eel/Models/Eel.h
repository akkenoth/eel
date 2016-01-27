#ifndef _MODELS_EEL_H
#define _MODELS_EEL_H

#include "RenderModel.h"

#define MOVEMENT_AMOUNT 0.5
#define MOVEMENT_SPEED 1.5

class Eel : public RenderModel {
private:
	std::vector<VertexFormat> vertices;
	std::vector<GLuint> indices;
	GLfloat length;
	GLfloat radius;
	GLuint sectors;
	glm::vec4 color;
public:
	Eel();
	~Eel();

	void create(GLfloat length, GLfloat radius, GLuint sectors, const glm::vec4& color = glm::vec4(0.0f));
	void construct(const float time, bool init = false);
	virtual void update(const float totalTimePassed = 0.0f, const float deltaTime = 0.0f) override final;
	virtual void draw(const GLuint program) override final;
};

#endif // !_MODELS_EEL_H
