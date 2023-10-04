
#ifndef TEXTURE_H
#define TEXTURE_H
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <sstream>

class Texture
{
public:

	Texture(const std::string& imagePath, GLenum textureTarget = GL_TEXTURE_2D);
	~Texture();
	void bind(GLenum textureUnit = GL_TEXTURE0) const;
	void unbind() const;
private:
	GLuint textureID;
	GLenum target;
};

#endif