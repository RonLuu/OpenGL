#ifndef VAO_CLASS_H
#define VAO_CLASS_H
#include <glad/glad.h>
#include "VBO.h"

class VAO
{
public:
	unsigned int VAO_ID;
	VAO()
	{
		glGenVertexArrays(1, &VAO_ID);
		Bind();
	}

	void Bind()
	{
		glBindVertexArray(VAO_ID);
	}

	void Unbind()
	{
		glBindVertexArray(0);
	}

	void Delete()
	{
		glDeleteVertexArrays(1, &VAO_ID);
	}

	void LinkVBO(VBO & VBO, GLuint layout, GLint startingIndex, GLsizei stride, const void * pointer)
	{
		VBO.Bind();
		glVertexAttribPointer(layout, startingIndex, GL_FLOAT, GL_FALSE, stride, pointer);
		glEnableVertexAttribArray(layout);
		VBO.Unbind();
	}
};

#endif