#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// The code for a specific vertex shader function
const char * vertexShaderSourceCode = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

// The code for a specific fragment shader function
const char * fragmentShaderSourceCode = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.5f, 1.0f);\n"
"}\n\0";

void processInput(GLFWwindow * window);

int main()
{

	// Initialise glfw first
	glfwInit();
	// Configure glfw setting
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a window
	#pragma region
	GLFWwindow * window = glfwCreateWindow(800, 600, "Hello Triangle", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}
	//??
	glfwMakeContextCurrent(window);
#pragma endregion
	// Load glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialise GLAD" << std::endl;
		return -1;
	}

	// Variables for any compilation error
	int success;
	char infoLog[512];

	//Get a vertex shader
	#pragma region 
	// Create a vertex shader object
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attatch the vertex shader code to the vertex shader object
	glShaderSource(vertexShader, 1, &vertexShaderSourceCode, NULL);
	// Compile the vertex shader function's code 
	glCompileShader(vertexShader);

	// Check for any compilation error
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
#pragma endregion
	// Get a fragment shader
	#pragma region
	// Creata a fragment shader object
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach the fragment shader code to the fragment shader object
	glShaderSource(fragmentShader, 1, &fragmentShaderSourceCode, NULL);
	// Compile the fragment shader function's code
	glCompileShader(fragmentShader);

	// Check for any compilation error
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
#pragma endregion
	// Get a program shader
	#pragma region
	// Create a shader program/ensemble shader
	unsigned int shaderProgram = glCreateProgram();
	// Attach the individual shaders
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Make a pipeline of shaders
	glLinkProgram(shaderProgram);

	// Check for any compilation error
	glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	#pragma endregion
	// Remove unncessary shaders
	#pragma region
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	#pragma endregion
	
	// Collection of vertices
	float vertices[] = {
	-0.4f, -0.5f, 0.0f, // Bottom left house
	0.4f,  -0.5f, 0.0f, // Bottom right house
	0.4f,   0.2f, 0.0f, //  Top right house
	-0.4f,  0.2f, 0.0f, //  Top left house
	-0.5f,  0.23f, 0.0f, // Bottom left triangle
	0.5f,   0.23f, 0.0f, // Bottom right triangle
	0.0f,   0.7f, 0.0f, // Top triangle
	};

	unsigned int indices[] = {
		0, 1, 2,
		0, 3, 2,
		4, 5, 6,
	};

	// Create a vertex buffer object to store vertices
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	// Create a vertex array object
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	
	// bind the Vertex Array Object
	glBindVertexArray(VAO);
	// Specify the buffer is for vertices by 
	// binding that buffer to an array type
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Copy the vertex data into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Tell openGL how to interpret the data vertex
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	//??
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}