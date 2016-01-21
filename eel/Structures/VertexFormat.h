#ifndef _STRUCTURES_VERTEXFORMAT_H
#define _STRUCTURES_VERTEXFORMAT_H

#include "../Libs/glm/glm.hpp"

struct VertexFormat {
	// X, Y, Z
	glm::vec3 position;
	// RGBA
	glm::vec4 color;
	// Texture X, Y
	glm::vec2 texture;

	VertexFormat() {}

	VertexFormat(const glm::vec3& pos, const glm::vec4& col) {
		position = pos;
		color = col;
		texture.x = texture.y = 0;
	}

	VertexFormat(const glm::vec3& pos, const glm::vec2& tex) {
		position = pos;
		color.r = color.g = color.b = color.a = 0;
		texture = tex;
	}
};

#endif // !_STRUCTURES_VERTEXFORMAT_H
