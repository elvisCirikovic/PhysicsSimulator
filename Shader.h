
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <sstream>

#ifndef SHADER_H
#define SHADER_H
class Shader
{	
public:
	unsigned int id;
	//constructor
	Shader(const char* vertexSource, const char* fragmentSource);

	//use the shader program
	void use();

	//utility functions
	void setBool(const std::string &name, bool value) const ;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;


	~Shader();


};
#endif