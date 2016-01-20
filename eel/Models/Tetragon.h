#ifndef _MODELS_TETRAGON_H
#define _MODELS_TETRAGON_H

#include "RenderModel.h"

class Tetragon : public RenderModel {
public:
	Tetragon();
	~Tetragon();

	void create();
	virtual void update() override final;
	virtual void draw() override final;
};

#endif // !_MODELS_TETRAGON_H
