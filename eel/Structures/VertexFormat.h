#ifndef _STRUCTURES_VERTEXFORMAT_H
#define _STRUCTURES_VERTEXFORMAT_H

#include "../Libs/glm/glm.hpp"

class VertexFormat {
public:
	// X, Y, Z
	glm::vec3 position;
	// Normal
	glm::vec3 normal;
	// RGBA
	glm::vec4 color;
	// Texture X, Y
	glm::vec2 texture;

	VertexFormat() {}

	VertexFormat(const glm::vec3& pos, const glm::vec4& col = glm::vec4(0.0f), const glm::vec2& tex = glm::vec2(0.0f)) {
		construct(pos, pos, tex, col);
	}

	VertexFormat(const glm::vec3& pos, const glm::vec2& tex = glm::vec2(0.0f), const glm::vec4& col = glm::vec4(0.0f)) {
		construct(pos, pos, tex, col);
	}

	VertexFormat(const glm::vec3& pos, const glm::vec3& norm, const glm::vec4& col = glm::vec4(0.0f), const glm::vec2& tex = glm::vec2(0.0f)) {
		construct(pos, norm, tex, col);
	}

	VertexFormat(const glm::vec3& pos, const glm::vec3& norm, const glm::vec2& tex = glm::vec2(0.0f), const glm::vec4& col = glm::vec4(0.0f)) {
		construct(pos, norm, tex, col);
	}

private:
	void construct(const glm::vec3& pos, const glm::vec3& norm, const glm::vec2& tex, const glm::vec4& col) {
		position = pos;
		normal = glm::normalize(position);
		color = col;
		texture = tex;
	}
};

#endif // !_STRUCTURES_VERTEXFORMAT_H
