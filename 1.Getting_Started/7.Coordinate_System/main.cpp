#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 800;

void framebuffer_size_callback(GLFWwindow * window, int width, int height);
void processInput(GLFWwindow * window);

int main()
{
	glfwInit();
	glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwInitHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow * window = glfwCreateWindow(WIDTH, HEIGHT, "7. Coordinate System", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create a window\n";
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
	{
		std::cout << "Failed to initialise GLAD\n";
		return -1;
	}

	Shader myShader("x64/Debug/Shaders/shader.vert","x64/Debug/Shaders/shader.frag");
	

	float vertices[] = {
		// The back of the cube
		// Bottom right triangle
	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,	1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
		// Upper left triangle
	 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,

		// The front of the cube
		// Bottom right triangle
	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,		1.0f, 1.0f,
		// Upper left triangle
	 0.5f,  0.5f,  0.5f,		1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,	0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,

		// The leftside of the cube
		// The upper left triangle
	-0.5f,  0.5f,  0.5f,	1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
		// The bottom right of the cube
	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,	1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,		1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,		1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,	1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,		1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,		1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,	0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,	0.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	unsigned VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void *)0);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void *)(3 * sizeof(float)));
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void *)(6 * sizeof(float)));
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void *)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void *)(3 * sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	//glEnableVertexAttribArray(2);

	unsigned int texture1, texture2;
	int width, height, nChannels;
	unsigned char* data;

	glGenTextures(1, &texture1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glEnable(GL_DEPTH_TEST);

	stbi_set_flip_vertically_on_load(true);

	data = stbi_load("monkey_listen.jpg", &width, &height, &nChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture\n";
	}
	stbi_image_free(data);

	glGenTextures(1, &texture2);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("horizon.jpg", &width, &height, &nChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture\n";
	}
	stbi_image_free(data);
	
	
	myShader.use();
	myShader.setInt("texture1", 0);
	myShader.setInt("texture2", 1);
	myShader.setFloat("mixValue", 0.2f);


	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		projection = glm::perspective(glm::radians(45.0f), 1.0f * HEIGHT / WIDTH, 0.1f, 100.0f);
		
		myShader.use();
		myShader.setMat4("view", view);
		myShader.setMat4("projection", projection);

		glBindVertexArray(VAO);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			float angle = 20.0f * i;

			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			myShader.setFloat("mixValue", sinf(glfwGetTime())/2 + 0.5f);

			myShader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

}

void processInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}