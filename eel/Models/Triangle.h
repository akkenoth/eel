#ifndef _MODELS_TRIANGLE_H
#define _MODELS_TRIANGLE_H

#include "RenderModel.h"

class Triangle : public RenderModel {
public:
	Triangle();
	~Triangle();

	void create();
	virtual void update() override final;
	virtual void draw() override final;
};

#endif // !_MODELS_TRIANGLE_H
