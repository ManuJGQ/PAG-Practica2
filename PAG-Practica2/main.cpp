#include <iostream>
#include <string>

#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h> //glew SIEMPRE va antes del glfw
#include <GLFW/glfw3.h>
#include "gtc\matrix_transform.hpp"

#include "PagShaderProgram.h"

#include "PagAssistantClass.h"

int main(int argc, char** argv) {
	/*char* docdir = getenv("userprofile");
	std::string path = docdir;
	std::string archivo;
	path += "/Desktop/";
	std::cout << "Escriba el nombre del fichero (con .txt)" << std::endl;
	std::getline(std::cin, archivo);
	path += archivo;

	int slices;
	std::cout << "Escriba el numero de slices" << std::endl;
	std::cin >> slices;
	PagAssistantClass(path, slices, archivo);
	system("pause");*/

	struct PagPositionColor {
		glm::vec3 position;
		glm::vec3 color;
	};

	fprintf(stderr, "Starting application\n");

	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

	GLFWwindow* window;
	window = glfwCreateWindow(1024, 768, "PAG practice", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window\n");
		glfwTerminate();
		return -2;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		glfwTerminate();
		return -3;
	}

	//fprintf(stderr, "%s\n", glGetString(GL_RENDERER));
	//fprintf(stderr, "%s\n", glGetString(GL_VENDOR));
	//fprintf(stderr, "%s\n", glGetString(GL_VERSION));
	//fprintf(stderr, "%s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_PROGRAM_POINT_SIZE);
	glViewport(0, 0, 1024, 768);

	PagShaderProgram pepe;
	//pepe.createShaderProgram("points");
	pepe.createShaderProgram("pointsMultiColor");

	GLfloat sizes[] = { 8.0f, 10.0f , 20.0f , 15.0f , 8.0f, 30.0f, 12.0f, 22.0f };

	PagPositionColor geometry[] = {

		{ glm::vec3(-1.0, -1.0, -10.0), glm::vec3(1.0, 0.0, 0.0) },
		{ glm::vec3(1.0,  -1.0, -10.0), glm::vec3(1.0, 0.0, 0.0) },
		{ glm::vec3(-1.0, 1.0, -10.0), glm::vec3(0.0, 0.0, 0.0) },
		{ glm::vec3(1.0, 1.0, -10.0), glm::vec3(0.0, 1.0, 0.0) },
		{ glm::vec3(-1.0, -1.0, -5.0), glm::vec3(0.0, 1.0, 0.0) },
		{ glm::vec3(1.0, -1.0, -5.0), glm::vec3(0.0, 0.0, 1.0) },
		{ glm::vec3(-1.0, 1.0, -5.0), glm::vec3(0.0, 0.0, 1.0) },
		{ glm::vec3(1.0, 1.0, -5.0), glm::vec3(0.0, 0.0, 0.0) },
	};

	glm::vec3 points[] = {
		glm::vec3(1.0, -1.0, -10.0),
		glm::vec3(-1.0,  1.0, -10.0),
		glm::vec3(1.0,  1.0, -10.0),
		glm::vec3(-1.0, -1.0, -5.0),
		glm::vec3(1.0, -1.0, -5.0),
		glm::vec3(-1.0,  1.0, -5.0),
		glm::vec3(1.0,  1.0, -5.0)
	};

	GLuint indices[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	GLuint indicesLeft[] = { 0, 2, 4, 6 };

	GLuint vao;
	GLuint vbo;
	GLuint vboSize;
	GLuint ibo;
	GLuint iboLeft;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);

	//glVertexAttribPointer(0, sizeof(glm::vec3) / sizeof(GLfloat),
	//	GL_FLOAT, GL_FALSE, sizeof(glm::vec3),
	//	((GLubyte *)NULL + (0)));

	glVertexAttribPointer(0, sizeof(glm::vec3) / sizeof(GLfloat),
		GL_FLOAT, GL_FALSE, sizeof(PagPositionColor),						//POSITIONS
		((GLubyte *)NULL + (0)));
	//MULTICOLOR
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, sizeof(glm::vec3) / sizeof(GLfloat),
		GL_FLOAT, GL_FALSE, sizeof(PagPositionColor),						//COLORS
		((GLubyte *)NULL + (sizeof(glm::vec3))));

	//glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	glBufferData(GL_ARRAY_BUFFER, sizeof(geometry), geometry, GL_STATIC_DRAW);

	glGenBuffers(1, &vboSize);
	glBindBuffer(GL_ARRAY_BUFFER, vboSize);									//Enlazamos en nuevo vbo

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, sizeof(GLfloat) / sizeof(GLfloat),
		GL_FLOAT, GL_FALSE, sizeof(GLfloat),						//TAMAÑOS
		((GLubyte *)NULL + (0)));

	glBufferData(GL_ARRAY_BUFFER, sizeof(sizes), sizes, GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glGenBuffers(1, &iboLeft);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboLeft);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesLeft), indicesLeft, GL_STATIC_DRAW);

	do {
		glClear(GL_COLOR_BUFFER_BIT);
		pepe.use();
		//pepe.setUniform("pointSize", 8.0f);
		//pepe.setUniform("vColor", glm::vec3(0.0f, 0.0f, 1.0f));		//No esta en el shader
		pepe.setUniform("mvpMatrix", glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.f));
		glBindVertexArray(vao);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboLeft);
		glDrawElements(GL_POINTS, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

	return 0;
}