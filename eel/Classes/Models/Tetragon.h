#pragma once

#include "../RenderModel.h"

class Tetragon : public RenderModel {
public:
	Tetragon();
	~Tetragon();

	void create();
	virtual void update() override final;
	virtual void draw() override final;
};
