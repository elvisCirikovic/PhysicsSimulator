#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#ifndef CAMERA_H
#define CAMERA_H

class Camera
{	
public:

	Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up);
	glm::mat4 getViewMatrix();
	glm::vec3& getCameraPos();
	glm::vec3& getCameraFront();
	glm::vec3& getCameraUp();
	void setCameraPos(const glm::vec3& position);
	void setCameraFront(const glm::vec3& front);
	void setCameraUp(const glm::vec3& up);

private:
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	float pitch;
	float yaw;
};

#endif
