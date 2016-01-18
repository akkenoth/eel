#pragma once

#include "../Interfaces/RenderObject.h"

class RenderModel : public RenderObject {
protected:
	GLuint vao;
	GLuint program;
	std::vector<GLuint> vbos;
public:
	RenderModel();
	virtual ~RenderModel();

	virtual void draw() override;
	virtual void update() override;
	virtual void destroy() override;
	virtual void setProgram(GLuint program) override;

	virtual GLuint getVao() const override;
	virtual const std::vector<GLuint>& getVbos() const override;
};

