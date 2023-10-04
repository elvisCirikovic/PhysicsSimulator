#include "Window.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"
#include "Texture.h"



void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


int main()
{







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


	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};

	unsigned int indices[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
	};
	unsigned int VBO; //stores a large number of vertices in GPU memory
	glGenBuffers(1, &VBO); //generates a buffer id
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //binds vbo to GL_ARRAY_BUFFER

	Shader shaderProgram("shaders/testShader.vs", "shaders/testShader.fsc");


	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);




	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //copies user-defined data into the currently bound buffer

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); // Position attribute
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); // Color attribute
	glEnableVertexAttribArray(1);


	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	Texture wallTexture("wall.jpg");




	//keeps running the window until we tell it to stop
	while (!glfwWindowShouldClose(myWindow))
	{
		//input
		simWindow.processInput(myWindow);

		//render
		glClearColor(0.2f, 0.1f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//render container
		
		wallTexture.bind();
		shaderProgram.use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		//buffer swappers and IO events
		glfwSwapBuffers(myWindow);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}




