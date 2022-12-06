#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include <cmath>


main()
{
	//Initialize
	glfwInit();

	//Tell OGL what version to  use and what profile (I did modern or core but there is also the outdated ones)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Window variable set to create window (Width, Height. Window name, Fullscreen, not important...)
	GLFWwindow* window = glfwCreateWindow(800, 600,  "EggSimulator", NULL, NULL);
	if(window == NULL)
	{
		std::cout << "Failed to create window :(" << std::endl;
		glfwTerminate();
		return -1;
	}

	//Tells OGL there is window
	glfwMakeContextCurrent(window);

	//Getting glad to work
	gladLoadGL();
	glViewport(0, 0, 800, 800);

	//Verices Coordinates
	//Vertice values between -1 and 1
	GLfloat vertices[] = 
	{
		-0.5f, -1.0f * float(sqrt(3)) / 3, 0.0f, //Bottom Left
		0.5f, -1.0f * float(sqrt(3)) / 3, 0.0f, //Bottom Right
		0.0f, 0.25f * float(sqrt(3)) * 2 / 3, 0.0f, //Top
		-0.25f, -0.375f * float(sqrt(3)) / 6, 0.0f, //Inner left
		0.25f, -0.375f * float(sqrt(3)) / 6, 0.0f, //Inner right
		0.0f, -1.0f * float(sqrt(3)) / 3, 0.0f //Inner down
	};

	GLuint indices[] =
	{
		0, 3, 5, //Lower left Triangle vertice order
		5, 1, 4, //Lower right Triangle vertice order
		2, 3, 4 //Upper Triangle vertice order
	};

	// Create reference containers for the Vartex Array Object and the Vertex Buffer Object
	GLuint VAO, VBO, EBO;

	// Generate the VAO and VBO with only 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(VAO);

	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// Enable the Vertex Attribute so that OpenGL knows to use it
	glEnableVertexAttribArray(0);

	// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	while(!glfwWindowShouldClose(window))
	{
		//Change background color
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//Creating Triangle
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		//Swapping Front Buffer with Back Buffer (Updating the screen)
		glfwSwapBuffers(window);

		//Process all events ex: resize window
		glfwPollEvents();
	}

	//Delete shaders and stuff after use
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &EBO);

	//Delete window
	glfwDestroyWindow(window);
	//Oposite of initialize
	glfwTerminate();
	return 0;
}