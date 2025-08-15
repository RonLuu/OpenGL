#ifndef VBO_CLASS_H
#define VBO_CLASS_H
#include <glad/glad.h>

class VBO
{
public:
	unsigned int VBO_ID;
	// Generate and Bind VBO
	VBO(GLfloat * vertices, GLsizeiptr size)
	{
		glGenBuffers(1, &VBO_ID);
		Bind();
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}
	// Bind VBO
	void Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO_ID);
	}

	// Unbind VBO
	void Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	// Delete VBO
	void Delete()
	{
		glDeleteBuffers(1, &VBO_ID);
	}
};

#endif