#ifndef _ENGINE_CAMERA_H
#define _ENGINE_CAMERA_H

#include "../Libs/glm/glm.hpp"
#include "../Libs/glm/gtc/matrix_transform.hpp"
#include "../Libs/glm/gtx/rotate_vector.hpp"

#ifndef M_PI
#define M_PI 3.141592f
#endif // !M_PI

#define CAMERA_SPEED 5.0f
#define CAMERA_ROTATION_SPEED 0.001f
#define CAMERA_MAX_Y_ANGLE 1.57f // _almost_ M_PI/2

class Camera {
private:
	glm::vec3 position;
	glm::vec3 direction;
	// Angle in XY plane
	float angleX;
	// Angle in YZ plane
	float angleY;
	// "UP" vector
	glm::vec3 orientation;
	float aspectRatio;
	float verticalFOV;
	float nearClip;
	float farClip;
public:
	Camera(glm::vec3 p, glm::vec3 d = glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3 o = glm::vec3(0.0f, 1.0f, 0.0f), float aR = 1.0f, float vFOV = 50.0f, float nC = 0.1f, float fC = 100.0f);
	~Camera();

	void setAspectRatio(float aR);
	void move(float time, bool forward, bool backward, bool left, bool right);
	void rotate(float time, int x, int y);

	glm::mat4 getViewMatrix() const;
	glm::mat4 getProjectionMatrix() const;
	glm::vec3 getEyePosition() const;
};

#endif // !_ENGINE_CAMERA_H
