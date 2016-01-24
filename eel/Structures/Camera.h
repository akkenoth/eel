#ifndef _STRUCTURES_CAMERA_H
#define _STRUCTURES_CAMERA_H

#include "../Libs/glm/glm.hpp"

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif // !M_PI

struct Camera {
	glm::vec3 position;
	glm::vec3 direction;
	// "UP" vector
	glm::vec3 orientation;
	float aspectRatio;
	float verticalFOV;
	float nearClip;
	float farClip;

	Camera(glm::vec3 p, glm::vec3 d = glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3 o = glm::vec3(0.0f, 1.0f, 0.0f), float aR = 1.0f, float vFOV = 50.0f, float nC = 0.1f, float fC = 100.0f) {
		position = p;
		orientation = glm::normalize(o);
		direction = glm::normalize(d);
		if(aR <= 0.0f) {
			aR = 1.0f;
		}
		aspectRatio = aR;
		if(vFOV <= 0.0f || vFOV > 180.0f) {
			// default to 50* - it's 90* on 16:9 monitor
			vFOV = 50.0f;
		}
		verticalFOV = vFOV * (float)(M_PI) / 180.0f;
		if(nC <= 0.0f) {
			nC = 0.1f;
		}
		nearClip = nC;
		if(fC > 1000.0f) {
			fC = 1000.0f;
		}
		farClip = fC;
	}
};

#endif // !_STRUCTURES_CAMERA_H
