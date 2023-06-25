#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#ifndef WINDOW_H
#define WINDOW_H

class Window
{
public:

	Window(int height, int width, const char* title);  //constructor

	
	void processInput(GLFWwindow* window);

	//getters and setter functions
	int getWindowHeight();
	int getWindowWidth();
	const char* getWindowTitle();
	void setWindowHeight(int height);
	void setWindowWidth(int width);
	GLFWwindow* getGLFWWindow();


private:

	GLFWwindow* m_window;

	int m_height;

	int m_width;

	const char* m_title;

};


#endif 