#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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

	//setting up the camera for the 3D space
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	Camera mainCamera(cameraPos, cameraFront, cameraUp);


	glEnable(GL_DEPTH_TEST);


	//disables cursor in the window
	glfwSetInputMode(myWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//GUI INIT BELOW 
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(myWindow, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	Shader shaderProgram("shaders/testShader.vs", "shaders/testShader.fsc");


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
		


		//std::cout << "Actual Camera pos is: (" << cameraPos.x << ", " << cameraPos.y << ", " << cameraPos.z << ")\n";

		//render
		glClearColor(0.2f, 0.1f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//SIMPLE WINDOW TEST
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		//render container

		glm::vec3 temporaryVector = testCube.getPosition(testCube);

		//this is just a test, trying to move the cube slightly along the x plane
		std::cout << "Cube's Position is: (" << temporaryVector.x << "," << temporaryVector.y << "," << temporaryVector.z << ")\n";

		testCube.setPosition(glm::vec3(temporaryVector.x+.0005,temporaryVector.y,temporaryVector.z));

		testCube.Draw(shaderProgram);
		


		// create transformations
		glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		glm::mat4 view = glm::mat4(1.0f);
		float radius = 10.0f;
		float camX = static_cast<float>(sin(glfwGetTime()) * radius);
		float camZ = static_cast<float>(cos(glfwGetTime()) * radius);
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		glm::mat4 projection = glm::mat4(1.0f);

		// ROTATES CUBE MIGHT DELETE LATER: model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		

		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		projection = glm::perspective(glm::radians(45.0f), (float)simWindow.getWindowWidth() / (float)simWindow.getWindowHeight(), 0.1f, 100.0f);
		unsigned int modelLoc = glGetUniformLocation(shaderProgram.id, "model");
		unsigned int viewLoc = glGetUniformLocation(shaderProgram.id, "view");
		shaderProgram.setMat4("model", model);
		shaderProgram.setMat4("view", view);
		shaderProgram.setMat4("projection", projection);

		

	

		ImGui::Begin("Test Window");
		ImGui::Text("i pray this works");
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//buffer swappers and IO events
		glfwSwapBuffers(myWindow);
		glfwPollEvents();
	}

	//destroying the gui after the main loop is finished
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}
