#include "Window.h"
#include "Camera.h"
#include "globals.h"
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Window::Window(int width, int height, const char* title) : m_width(width), m_height(height), m_title(title)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (!glfwInit()) //handles init failures
	{
		std::cout << "Failed to init window" << std::endl;
		glfwTerminate();
		

	}

	m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL); //creates the window

	if (!m_window) //failed to make window
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
	}

	lastX = width / 2;
	lastY = height / 2;
	yaw = -90.0f;
	pitch = 0.0f;

	isFullScreen = false;
}



void Window::processInput(GLFWwindow* window, Camera camera, glm::vec3& cameraPos, glm::vec3& cameraFront, glm::vec3& cameraUp)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	//const float cameraSpeed = 0.05f;
	float cameraSpeed = static_cast<float>(2.5*DELTA_TIME); // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		cameraPos += cameraSpeed * cameraFront;
		//camera.setCameraPos(cameraPos);
		//std::cout << "W key pressed - cameraPos: (" << cameraPos.x << ", " << cameraPos.y << ", " << cameraPos.z << ")\n";
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		cameraPos -= cameraSpeed * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_CONTROL))
	{
		if (!isFullScreen)
		{
			//switch to full screen mode
			glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, 1920, 1080, GLFW_DONT_CARE);
			isFullScreen = true;
		}
		else
		{
			//switch to window mode
			glfwSetWindowMonitor(window, nullptr, 100, 100, m_width, m_height, GLFW_DONT_CARE);
			isFullScreen = false;
		}

	}
}

int Window::getWindowHeight()
{
	return m_height;
}

int Window::getWindowWidth()
{
	return m_width;
}

const char* Window::getWindowTitle()
{
	return m_title;
}

void Window::setWindowHeight(int height)
{
	m_height = height;
}

void Window::setWindowWidth(int width)
{
	m_width = width;
}

GLFWwindow* Window::getGLFWWindow()
{
	return m_window;
}

void Window::mouse_callBack(double xpos, double ypos, glm::vec3& cameraFront)
{
	if (FIRST_MOUSE)
	{
		lastX = xpos;
		lastY = ypos;
		FIRST_MOUSE = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; //reversed since y coords range from bottom to top
	lastX = xpos;
	lastY = ypos;

	const float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	else if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
}









