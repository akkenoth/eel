#ifndef _INTERFACES_RENDEROBJECT_H
#define _INTERFACES_RENDEROBJECT_H

#include <vector>
#include <iostream>
#include "../Libs/GLWrapper.h"
#include "../Structures/VertexFormat.h"

class RenderObject {
public:
	virtual ~RenderObject() = 0;

	virtual void draw() = 0;
	virtual void draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix) = 0;
	virtual void update() = 0;
	virtual void destroy() = 0;
	virtual void setProgram(GLuint shaderName) = 0;

	virtual GLuint getVao() const = 0;
	virtual const std::vector<GLuint>& getVbos() const = 0;
};

inline RenderObject::~RenderObject() {}

#endif // !_INTERFACES_RENDEROBJECT_H
