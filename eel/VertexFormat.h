#pragma once

#include "Libs/glm/glm.hpp"

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