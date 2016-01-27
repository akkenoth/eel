#ifndef _INTERFACES_RENDEROBJECT_H
#define _INTERFACES_RENDEROBJECT_H

#include <vector>
#include <map>
#include <iostream>
#include "../Libs/GLWrapper.h"
#include "../Engine/TextureLoader.h"
#include "../Structures/VertexFormat.h"

class RenderObject {
public:
	virtual ~RenderObject() = 0;

	virtual void draw() = 0;
	virtual void draw(const GLuint program) = 0;
	virtual void update(const float totalTimePassed = 0.0f, const float deltaTime = 0.0f) = 0;
	virtual void toggleAnimation() = 0;
	virtual void destroy() = 0;

	virtual GLuint getVao() const = 0;
	virtual const std::vector<GLuint>& getVbos() const = 0;
};

inline RenderObject::~RenderObject() {}

#endif // !_INTERFACES_RENDEROBJECT_H
