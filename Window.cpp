#include "Window.h"
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


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

	
}



void Window::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
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









