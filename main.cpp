#include "Window.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main()
{
	//std::cout << "Hello World";

	float vertices[] =
	{
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.05f,
		0.0f, 0.5f, 0.05f
	};
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	Window simWindow(800, 600, "test");
	GLFWwindow* myWindow = simWindow.getGLFWWindow(); //simWindow is the custom created Window class and myWindow is the glfwWindow object derived from the simWindow

	//makes the window
	glfwMakeContextCurrent(myWindow);
	

	//inits glad before we start using opengl functions
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
	//telling openGL the size of the rendering window
	glViewport(0, 0, simWindow.getWindowHeight(), simWindow.getWindowWidth());

	//resizes window when user or OS resizes it
	glfwSetFramebufferSizeCallback(myWindow, framebuffer_size_callback);

	//keeps running the window until we tell it to stop
	while (!glfwWindowShouldClose(myWindow))
	{
		simWindow.processInput(myWindow);

		glClearColor(0.8f, 0.1f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(myWindow);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}




