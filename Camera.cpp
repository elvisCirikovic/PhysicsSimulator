#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up)
	: cameraPos(position), cameraFront(front), cameraUp(up) 
{

}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

glm::vec3& Camera::getCameraPos()
{
	return cameraPos;
}

glm::vec3& Camera::getCameraFront()
{
	return cameraFront;
}

glm::vec3& Camera::getCameraUp()
{
	return cameraUp;
}

void Camera::setCameraPos(const glm::vec3& position)
{
	cameraPos = position;
}

void Camera::setCameraFront(const glm::vec3& front)
{
	cameraFront = front;
}

void Camera::setCameraUp(const glm::vec3& up)
{
	cameraUp = up;
}
