#include <iostream>
#include <string>
#include "Camera.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#ifndef WINDOW_H
#define WINDOW_H

class Window
{
public:

	Window(int height, int width, const char* title);  //constructor

	bool isFullScreen;

	void processInput(GLFWwindow* window, Camera camera, glm::vec3& cameraPos, glm::vec3& cameraFront, glm::vec3& cameraUp);

	//getters and setter functions
	int getWindowHeight();
	int getWindowWidth();
	const char* getWindowTitle();
	void setWindowHeight(int height);
	void setWindowWidth(int width);
	GLFWwindow* getGLFWWindow();

	void mouse_callBack(double xpos, double ypos, glm::vec3& cameraFront);
	
	float lastX;
	float lastY;


private:

	GLFWwindow* m_window;

	int m_height;

	int m_width;

	const char* m_title;

	float yaw;
	float pitch;

};


#endif 