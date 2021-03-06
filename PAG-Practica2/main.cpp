#include <iostream>
#include <string>

#include <GL/glew.h> //glew SIEMPRE va antes del glfw
#include <GLFW/glfw3.h>
#include "gtc\matrix_transform.hpp"

#include "PagShaderProgram.h"

#include "Pag3DGroup.h"
#include "Structs.h"
#include "PagRevolutionObject.h"

int main(int argc, char** argv) {
	// Leemos los datos y txt del usuario
	int perfiles;
	std::cout << "Introduce el numero de perfiles" << std::endl;
	std::cin >> perfiles;

	Structs::Fichero *ficheros = new Structs::Fichero[perfiles];

	int j = perfiles;
	while (j != 0) {
		char* docdir = getenv("userprofile");
		std::string path = docdir;
		std::string archivo;
		path += "/Desktop/";
		std::cout << "Escriba el nombre del fichero " << perfiles - j + 1 << " (con .txt)" << std::endl;
		std::cin >> archivo;
		path += archivo;

		Structs::Fichero _fichero;
		_fichero.nombreAlumno = archivo;
		_fichero.archivoIN = path;
		ficheros[perfiles - j] = _fichero;
		j--;
	}

	int slices;
	std::cout << "Escriba el numero de slices" << std::endl;
	std::cin >> slices;

	for (int i = 0; i < perfiles; i++) {
		ficheros[i].numSlices = slices;
	}

	//Creamos la jerarquia de objetos
	Pag3DGroup objects;
	PagRevolutionObject object;
	if (perfiles > 1) {
		objects = Pag3DGroup(ficheros, perfiles);
	}
	else object = PagRevolutionObject(Structs::Fichero(ficheros[0]));

	//Preparamos la ventana
	std::cout << "Starting application" << std::endl;

	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

	GLFWwindow* window;
	window = glfwCreateWindow(1024, 768, "PAG Practica 2", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to open GLFW window" << std::endl;
		glfwTerminate();
		return -2;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		return -3;
	}

	std::cout << glGetString(GL_RENDERER) << std::endl;
	std::cout << glGetString(GL_VENDOR) << std::endl;
	std::cout << glGetString(GL_VERSION) << std::endl;
	std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_PROGRAM_POINT_SIZE);
	glViewport(0, 0, 1024, 768);

	//Creamos las Geometrias y Topologias de los diferentes objetos
	if (perfiles > 1) {
		objects.createObject();
	}
	else {
		object.createObject();
	}

	//Dibujamos los objetos
	do {
		glClear(GL_COLOR_BUFFER_BIT);

		glm::mat4 ProjectionMatrix = glm::mat4(1.0f);
		glm::mat4 ViewMatrix = glm::mat4(1.0f);
		ProjectionMatrix *= glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.f);
		ViewMatrix *= glm::lookAt(glm::vec3(20.0, 20.0, -20.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

		glm::mat4 ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
		
		if (perfiles > 1) {
			objects.drawPointsCloud(ViewProjectionMatrix);
		}
		else {
			object.drawPointsCloud(ViewProjectionMatrix);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

	delete[] ficheros;
	return 0;
}
