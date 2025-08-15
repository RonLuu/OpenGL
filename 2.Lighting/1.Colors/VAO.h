#ifndef VAO_CLASS_H
#define VAO_CLASS_H
#include <glad/glad.h>
#include "VBO.h"

class VAO
{
public:
	
	unsigned int VAO_ID;
	// Generate and Bind VAO
	VAO()
	{
		glGenVertexArrays(1, &VAO_ID);
		Bind();
	}
	// Bind VAO
	void Bind()
	{
		glBindVertexArray(VAO_ID);
	}
	// Unbind VAO
	void Unbind()
	{
		glBindVertexArray(0);
	}
	
	// Delete VAO
	void Delete()
	{
		glDeleteVertexArrays(1, &VAO_ID);
	}

	// Link VBO
	void LinkVBO(VBO & VBO, GLuint layout, GLint startingIndex, GLsizei stride, const void * pointer)
	{
		VBO.Bind();
		glVertexAttribPointer(layout, startingIndex, GL_FLOAT, GL_FALSE, stride, pointer);
		glEnableVertexAttribArray(layout);
		VBO.Unbind();
	}
};

#endif