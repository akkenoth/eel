#ifndef _MODELS_TETRAGON_H
#define _MODELS_TETRAGON_H

#include "RenderModel.h"

class Tetragon : public RenderModel {
public:
	Tetragon();
	~Tetragon();

	void create();
	virtual void update(const float totalTimePassed = 0.0f, const float deltaTime = 0.0f) override final;
	virtual void draw(const GLuint program) override final;
};

#endif // !_MODELS_TETRAGON_H
