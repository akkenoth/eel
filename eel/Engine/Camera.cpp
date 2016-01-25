#include "Camera.h"
#include <iostream>

Camera::Camera(glm::vec3 p, glm::vec3 d, glm::vec3 o, float aR, float vFOV, float nC, float fC) {
	position = p;
	direction = glm::normalize(d);
	angleX = glm::acos(-d.z);
	angleY = glm::atan(d.y, d.x);
	std::cout << "camera angles: " << angleX <<" | "<< angleY << "\n";
	orientation = glm::normalize(o);
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

Camera::~Camera() {}

void Camera::setAspectRatio(float aR) {
	if(aR <= 0.0f) {
		aR = 1.0f;
	}
	aspectRatio = aR;
}

void Camera::move(float time, bool forward, bool backward, bool left, bool right) {
	glm::vec4 translation(0.0f);
	translation.w = 1.0f;

	if(forward && !backward) {
		translation.y = -1.0f;
	} else if(!forward && backward) {
		translation.y = 1.0f;
	}

	if(left && !right) {
		translation.x = -1.0f;
	} else if(!left && right) {
		translation.x = 1.0f;
	}

	glm::mat4 rotation = glm::orientation(direction, orientation);
	glm::vec4 translationRotated = translation * rotation;
	position += glm::vec3(translationRotated);
}

void Camera::rotate(float time, int x, int y) {
	// Todo: improve
	angleX += CAMERA_ROTATION_SPEED * x / aspectRatio;
	angleY += CAMERA_ROTATION_SPEED * y;
	direction = glm::rotateY(glm::rotateX(glm::vec3(0.0f, 0.0f, -1.0f), angleX), angleY);
}

glm::mat4 Camera::getViewMatrix() const {
	return glm::lookAt(position, position + direction, orientation);
};

glm::mat4 Camera::getProjectionMatrix() const {
	return glm::perspective(verticalFOV, aspectRatio, nearClip, farClip);
};

glm::vec3 Camera::getEyePosition() const {
	return position;
};
