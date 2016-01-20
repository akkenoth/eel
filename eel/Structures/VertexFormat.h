#ifndef _STRUCTURES_VERTEXFORMAT_H
#define _STRUCTURES_VERTEXFORMAT_H

#include "../Libs/GLMWrapper.h"

struct VertexFormat {
	// X, Y, Z
	glm::vec3 position;
	// RGBA
	glm::vec4 color;

	VertexFormat(const glm::vec3& pos, const glm::vec4& col) {
		position = pos;
		color = col;
	}
};

#endif // !_STRUCTURES_VERTEXFORMAT_H
