#include "Window.h"
#include "Camera.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"
#include "Texture.h"
#include "globals.h"
#include "Cube.h"




float DELTA_TIME = 0.0f;
float LAST_FRAME = 0.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


int main()
{


	Window simWindow(1200, 800, "test");
	GLFWwindow* myWindow = simWindow.getGLFWWindow(); //simWindow is the custom created Window class and myWindow is the glfwWindow object derived from the simWindow

	//makes the window
	glfwMakeContextCurrent(myWindow);


	//inits glad before we start using opengl functions
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
	//telling openGL the size of the rendering window
	glViewport(0, 0, simWindow.getWindowWidth(), simWindow.getWindowHeight());

	//resizes window when user or OS resizes it
	glfwSetFramebufferSizeCallback(myWindow, framebuffer_size_callback);

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	Camera mainCamera(cameraPos, cameraFront, cameraUp);


	glEnable(GL_DEPTH_TEST);

	glfwSetInputMode(myWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	float vertices[] = {
		// Positions          // Texture coordinates
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

		 0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	/*unsigned int indices[] = {
		0, 1, 2, // First triangle
		2, 3, 0  // Second triangle
	};*/
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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); // Position attribute
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))); // Color attribute
	glEnableVertexAttribArray(1);


	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	Texture wallTexture("wall.jpg");

	Cube testCube;



	//keeps running the window until we tell it to stop
	while (!glfwWindowShouldClose(myWindow))
	{

		//per frame time logic
		float currentFrame = static_cast<float>(glfwGetTime());
		DELTA_TIME = currentFrame - LAST_FRAME;
		LAST_FRAME = currentFrame;

		//std::cout << "Current Frame is " << currentFrame << std::endl;
		//std::cout << "Delta Time is  " << DELTA_TIME << std::endl;
		//std::cout << "Last Frame is  " << LAST_FRAME << std::endl;

		//input
		simWindow.processInput(myWindow, mainCamera, cameraPos, cameraFront, cameraUp);
		//simWindow.mouse_callBack(1.0, 2.0, cameraFront);
		double mouseX, mouseY;
		glfwGetCursorPos(myWindow, &mouseX, &mouseY);
		simWindow.mouse_callBack(mouseX, mouseY, cameraFront);
		


		std::cout << "Actual Camera pos is: (" << cameraPos.x << ", " << cameraPos.y << ", " << cameraPos.z << ")\n";

		//render
		glClearColor(0.2f, 0.1f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//render container

		wallTexture.bind();
		shaderProgram.use();
		
		testCube.Draw(shaderProgram, wallTexture);
		


			// create transformations
		glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		glm::mat4 view = glm::mat4(1.0f);
		float radius = 10.0f;
		float camX = static_cast<float>(sin(glfwGetTime()) * radius);
		float camZ = static_cast<float>(cos(glfwGetTime()) * radius);
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		glm::mat4 projection = glm::mat4(1.0f);
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));


		//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		projection = glm::perspective(glm::radians(45.0f), (float)simWindow.getWindowWidth() / (float)simWindow.getWindowHeight(), 0.1f, 100.0f);
		unsigned int modelLoc = glGetUniformLocation(shaderProgram.id, "model");
		unsigned int viewLoc = glGetUniformLocation(shaderProgram.id, "view");
		// pass them to the shaders (3 different ways)
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
		// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		shaderProgram.setMat4("projection", projection);

		glBindVertexArray(VAO);
		// UNCOMMENT SOON glDrawArrays(GL_TRIANGLES, 0, 36);
	

		//glDrawArrays(GL_TRIANGLES, 0, 3);

		//buffer swappers and IO events
		glfwSwapBuffers(myWindow);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}




