#ifndef TEXTURE_H
#define TEXTURE_H

#include <stb/stb_image.h>
#include <glad/glad.h>
#include <iostream>

class Texture
{
public:
	unsigned int textureID;
	GLenum textureType;
	// Generates and Binds Texture
	Texture(GLenum texture)
	{
		glGenTextures(1, &textureID);
		Bind();
		textureType = texture;
	}
	// Bind Texure
	void Bind()
	{
		glBindTexture(GL_TEXTURE_2D, textureID);
	}

	void SetWraping()
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	void SetFiltering()
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	void SetImage(const char * imagePath)
	{
		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
		unsigned char * data = stbi_load(imagePath, &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);
	}

	void ActiveAndBind()
	{
		glActiveTexture(textureType);
		glBindTexture(GL_TEXTURE_2D, textureID);
	}
};

#endif