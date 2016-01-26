#include "Camera.h"

Camera::Camera(glm::vec3 p, glm::vec3 d, glm::vec3 o, float aR, float vFOV, float nC, float fC) {
	position = p;
	direction = glm::normalize(d);
	angleX = glm::acos(-d.z);
	angleY = glm::atan(d.y, d.x);
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
	if(!forward && !backward && !left && !right) {
		return;
	}

	glm::vec3 translation(0.0f);
	if(forward && !backward) {
		translation.z = -1.0f;
	} else if(!forward && backward) {
		translation.z = 1.0f;
	}
	if(left && !right) {
		translation.x = -1.0f;
	} else if(!left && right) {
		translation.x = 1.0f;
	}

	position += glm::rotateY(glm::rotateX(translation, angleY), angleX) * time * CAMERA_SPEED;
}

void Camera::rotate(float time, int x, int y) {
	if(x == 0 && y == 0) {
		return;
	}

	/// Todo: improve by using screen height/width, aspect ratio etc
	angleX -= CAMERA_ROTATION_SPEED * x;
	if(angleX < 0.0f) {
		angleX += 2.0f * M_PI;
	} else if(angleX >= 2 * M_PI) {
		angleX -= 2.0f * M_PI;
	}
	angleY -= CAMERA_ROTATION_SPEED * y;
	if(angleY <= -CAMERA_MAX_Y_ANGLE) {
		angleY = -CAMERA_MAX_Y_ANGLE;
	} else if(angleY >= CAMERA_MAX_Y_ANGLE) {
		angleY = CAMERA_MAX_Y_ANGLE;
	}

	direction = glm::rotateY(glm::rotateX(glm::vec3(0.0f, 0.0f, -1.0f), angleY), angleX);
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
