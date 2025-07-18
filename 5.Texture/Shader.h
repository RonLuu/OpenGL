#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	unsigned int shaderID;

	Shader(const char * vertexPath, const char * fragPath)
	{
		std::string vertexCode;
		std::string fragCode;

		std::ifstream vertexFile;
		std::ifstream fragFile;

		vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fragFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			vertexFile.open(vertexPath);
			fragFile.open(fragPath);

			std::stringstream vertextStream, fragStream;
			vertextStream << vertexFile.rdbuf();
			fragStream << fragFile.rdbuf();

			vertexFile.close();
			fragFile.close();
			
			vertexCode = vertextStream.str();
			fragCode = fragStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "Failed to read shader files\n";
		}

		const char * vShaderCode = vertexCode.c_str();
		const char * fShaderCode = fragCode.c_str();

		int success;
		char infoLog[512];

		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vShaderCode, NULL);
		glCompileShader(vertexShader);
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "Failed to compile the vertex shader\n";
		}
		
		unsigned int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragShader, 1, &fShaderCode, NULL);
		glCompileShader(fragShader);
		glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
			std::cout << "Failed to compile the fragment shader\n";
		}

		shaderID = glCreateProgram();
		glAttachShader(shaderID, vertexShader);
		glAttachShader(shaderID, fragShader);
		glLinkProgram(shaderID);
		glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
			std::cout << "Failed to link the shaders\n";
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragShader);
	}

	void use()
	{
		glUseProgram(shaderID);
	}

	void setInt(const std::string &name, int value) const
	{
		glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value);
	}
};

#endif