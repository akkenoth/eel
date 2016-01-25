#ifndef _STRUCTURES_LIGHTSOURCE_H
#define _STRUCTURES_LIGHTSOURCE_H

#include "../Libs/glm/glm.hpp"

struct LightSource {
	// Light direction for not point lights (global illumination)
	glm::vec3 position;
	glm::vec3 color;
	float attenuationConstant;
	float attenuationLinear;
	float attenuationQuadratic;
	bool isPointLight;
	bool enabled;

	LightSource(const glm::vec3& p, const glm::vec3& c = glm::vec3(1.0f), const float& aC = 1.0f, const float& aL = 0.0f, const float& aQ = 0.0f, const bool& iPL = true) {
		position = p;
		color = c;
		attenuationConstant = aC;
		attenuationLinear = aL;
		attenuationQuadratic = aQ;
		isPointLight = iPL;
		enabled = true;
	}

	void toggle() {
		enabled = !enabled;
	}
};

#endif // !_STRUCTURES_LIGHTSOURCE_H
