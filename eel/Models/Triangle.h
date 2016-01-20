#pragma once

#include "RenderModel.h"

class Triangle : public RenderModel {
public:
	Triangle();
	~Triangle();

	void create();
	virtual void update() override final;
	virtual void draw() override final;
};
