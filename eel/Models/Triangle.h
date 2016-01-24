#ifndef _MODELS_TRIANGLE_H
#define _MODELS_TRIANGLE_H

#include "RenderModel.h"

class Triangle : public RenderModel {
public:
	Triangle();
	~Triangle();

	void create();
	virtual void update(const float totalTimePassed = 0.0f, const float deltaTime = 0.0f) override final;
	virtual void draw(const GLuint program) override final;
};

#endif // !_MODELS_TRIANGLE_H
