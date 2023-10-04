#include "Texture.h"
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

Texture::Texture(const std::string& imagePath, GLenum textureTarget) : target(textureTarget)
{
    glGenTextures(1, &textureID);
    glBindTexture(target, textureID);

    // Set the texture wrapping and filtering options
    glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load and generate the texture
    int width, height, nrChannels;
    unsigned char* data = stbi_load(imagePath.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(target, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(target);
    }
    else {
        std::cerr << "Failed to load texture: " << imagePath << std::endl;
    }
    stbi_image_free(data);
}

Texture::~Texture()
{
	glDeleteTextures(1, &textureID);
}

void Texture::bind(GLenum textureUnit) const
{
    glActiveTexture(textureUnit);
    glBindTexture(target, textureID);
}

void Texture::unbind() const
{
    glBindTexture(target, 0);
}
