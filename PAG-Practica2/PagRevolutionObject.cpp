#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h> //glew SIEMPRE va antes del glfw
#include <GLFW/glfw3.h>
#include "gtc\matrix_transform.hpp"

#include "PagShaderProgram.h"

#include "PagRevolutionObject.h"

#include <math.h>

#define PI 3.14159265358979323846

PagRevolutionObject::PagRevolutionObject() : flagBottomTape(false), flagTopTape(false),
geometria(nullptr), coordtext(nullptr), indices(nullptr), indicesBottomTape(nullptr),
indicesTopTape(nullptr), slices(0), tamaGeometriaCoordText(0), tamaIndices(0) {};

PagRevolutionObject::PagRevolutionObject(int _numPuntosPerfilOriginal, int _numDivisiones,
	PuntosPerfil& _perfilOriginal, bool _flagBottomTape, bool _flagTopTape, int _slices) :
	geometria(nullptr), coordtext(nullptr), indices(nullptr), indicesBottomTape(nullptr),
	indicesTopTape(nullptr), tamaGeometriaCoordText(0), tamaIndices(0) {

	flagBottomTape = _flagBottomTape;
	flagTopTape = _flagTopTape;

	subdivisionProfiles = PagSubdivisionProfile(_numPuntosPerfilOriginal, _numDivisiones,
		_perfilOriginal);

	slices = _slices;

	if (slices == 0) slices++;

}

void PagRevolutionObject::operator=(const PagRevolutionObject & orig) {
	flagBottomTape = orig.flagBottomTape;
	flagTopTape = orig.flagTopTape;
	slices = orig.slices;
	tamaGeometriaCoordText = orig.tamaGeometriaCoordText;
	tamaIndices = orig.tamaIndices;
	subdivisionProfiles = orig.subdivisionProfiles;

	if (orig.geometria != nullptr) {
		geometria = new Geometria[tamaGeometriaCoordText];
		for (int i = 0; i < tamaGeometriaCoordText; i++) {
			geometria[i].vertice = orig.geometria[i].vertice;
			geometria[i].normal = orig.geometria[i].normal;
			geometria[i].tangente = orig.geometria[i].tangente;
		}
	}
	else geometria = nullptr;

	if (orig.coordtext != nullptr) {
		coordtext = new CoordTexturas[tamaGeometriaCoordText];
		for (int i = 0; i < tamaGeometriaCoordText; i++) {
			coordtext[i] = orig.coordtext[i];
		}
	}
	else coordtext = nullptr;

	if (orig.indices != nullptr) {
		indices = new int[tamaIndices];
		for (int i = 0; i < tamaIndices; i++) {
			indices[i] = orig.indices[i];
		}
	}
	else indices = nullptr;

	if (orig.indicesBottomTape != nullptr) {
		indicesBottomTape = new int[slices + 1];
		for (int i = 0; i < slices + 1; i++) {
			indicesBottomTape[i] = orig.indicesBottomTape[i];
		}
	}
	else indicesBottomTape = nullptr;

	if (orig.indicesTopTape != nullptr) {
		indicesTopTape = new int[slices + 1];
		for (int i = 0; i < slices + 1; i++) {
			indicesTopTape[i] = orig.indicesTopTape[i];
		}
	}
	else indicesTopTape = nullptr;
}


void PagRevolutionObject::revolution() {
	int numPuntosPerfil = subdivisionProfiles.getNumPuntosPerfil();

	int numTapas = 0;
	int cambioIndice = 0;
	if (flagBottomTape) {
		numTapas++;
		cambioIndice++;

		indicesBottomTape = new int[slices + 1];
	}
	if (flagTopTape) {
		numTapas++;

		indicesTopTape = new int[slices + 1];
	}

	tamaGeometriaCoordText = ((numPuntosPerfil - numTapas) * slices) + numTapas;
	tamaIndices = (((numPuntosPerfil - (numTapas)) * 2) + 1) * slices;
	geometria = new Geometria[tamaGeometriaCoordText];
	coordtext = new CoordTexturas[tamaGeometriaCoordText];
	indices = new int[tamaIndices];

	PuntosPerfil *perfil = &subdivisionProfiles.getPerfil();

	double angleRadIncrement = (2 * PI) / slices;

	// VERTICES

	for (int j = 0; j < numPuntosPerfil; j++) {
		if (j == 0 && flagBottomTape) {
			PuntosVertices vert;
			vert.x = 0;
			vert.y = perfil[j].y;
			vert.z = 0;
			geometria[tamaGeometriaCoordText - numTapas].vertice = vert;
		}
		else if (j == numPuntosPerfil - 1 && flagTopTape) {
			PuntosVertices vert;
			vert.x = 0;
			vert.y = perfil[j].y;
			vert.z = 0;
			geometria[tamaGeometriaCoordText - 1].vertice = vert;
		}
		else {
			for (int i = 0; i < slices; i++) {
				double x = perfil[j].x * cos(angleRadIncrement * i);
				double z = perfil[j].x * -sin(angleRadIncrement * i);

				PuntosVertices vert;
				vert.x = x;
				vert.y = perfil[j].y;
				vert.z = z;
				geometria[(j - cambioIndice) * slices + i].vertice = vert;
			}
		}

	}


	// NORMALES

	for (int j = 0; j < numPuntosPerfil; j++) {
		if (j == 0 && flagBottomTape) {
			NormalesTangentes normal;

			normal.x = 0;
			normal.y = -1;
			normal.z = 0;

			geometria[tamaGeometriaCoordText - numTapas].normal = normal;
		}
		else if (j == numPuntosPerfil - 1 && flagTopTape) {
			NormalesTangentes normal;

			normal.x = 0;
			normal.y = 1;
			normal.z = 0;

			geometria[tamaGeometriaCoordText - 1].normal = normal;
		}
		else {
			for (int i = 0; i < slices; i++) {
				if (j == 1 && flagBottomTape) {
					NormalesTangentes normal;

					normal.x = 0;
					normal.y = -1;
					normal.z = 0;

					geometria[(j - cambioIndice) * slices + i].normal = normal;
				}
				else if (j == numPuntosPerfil - 2 && flagTopTape) {
					NormalesTangentes normal;

					normal.x = 0;
					normal.y = 1;
					normal.z = 0;

					geometria[(j - cambioIndice) * slices + i].normal = normal;
				}
				else {
					PuntosVertices p1;
					if (j == 0) p1 = { 0,0,0 };
					else p1 = geometria[(j - cambioIndice) * slices + i - 1].vertice;
					PuntosVertices pi = geometria[(j - cambioIndice) * slices + i].vertice;
					PuntosVertices p2 = geometria[(j - cambioIndice) * slices + i + 1].vertice;

					PuntosVertices v1;
					v1.x = pi.x - p1.x;
					v1.y = pi.y - p1.y;
					v1.z = pi.z - p1.z;

					double modV1 = sqrt((v1.x * v1.x) + (v1.y * v1.y) + (v1.z * v1.z));
					v1.x = v1.x / modV1;
					v1.y = v1.y / modV1;
					v1.z = v1.z / modV1;

					double xTemp = v1.x;
					v1.x = v1.y;
					v1.y = xTemp * -1;

					PuntosVertices vi;
					vi.x = p2.x - pi.x;
					vi.y = p2.y - pi.y;
					vi.z = p2.z - pi.z;

					double modVi = sqrt((vi.x * vi.x) + (vi.y * vi.y) + (vi.z * vi.z));
					vi.x = vi.x / modVi;
					vi.y = vi.y / modVi;
					vi.z = vi.z / modVi;

					xTemp = vi.x;
					vi.x = vi.y;
					vi.y = xTemp * -1;

					NormalesTangentes normal;

					normal.x = (v1.x + vi.x) / 2;
					normal.y = (v1.y + vi.y) / 2;
					normal.z = (v1.z + vi.z) / 2;

					geometria[(j - cambioIndice) * slices + i].normal = normal;
				}
			}
		}

	}

	// TANGENTES

	for (int j = 0; j < numPuntosPerfil; j++) {
		if (j == 0 && flagBottomTape) {
			NormalesTangentes tangente;

			tangente.x = 1;
			tangente.y = 0;
			tangente.z = 0;

			geometria[tamaGeometriaCoordText - numTapas].tangente = tangente;
		}
		else if (j == numPuntosPerfil - 1 && flagTopTape) {
			NormalesTangentes tangente;

			tangente.x = 1;
			tangente.y = 0;
			tangente.z = 0;

			geometria[tamaGeometriaCoordText - 1].tangente = tangente;
		}
		else {
			for (int i = 0; i < slices; i++) {
				NormalesTangentes tangente;

				tangente.x = -1 * sin(angleRadIncrement * i);
				tangente.y = 0;
				tangente.z = -1 * cos(angleRadIncrement * i);

				geometria[(j - cambioIndice) * slices + i].tangente = tangente;
			}
		}
	}

	// COORDENADAS TEXTURAS

	if (flagBottomTape || flagTopTape) {
		for (int i = 0; i < slices; i++) {
			double s = (cos(angleRadIncrement * float(i)) / 2.0) + 0.5;
			double t = (sin(angleRadIncrement * float(i)) / 2.0) + 0.5;
			if (flagBottomTape) {
				coordtext[i].s = s;
				coordtext[i].t = t;
			}
			if (flagTopTape) {
				coordtext[(numPuntosPerfil - numTapas - 1) * slices + i].s = s;
				coordtext[(numPuntosPerfil - numTapas - 1) * slices + i].t = t;
			}
		}
		if (flagBottomTape) {
			coordtext[tamaGeometriaCoordText - numTapas].s = 0.5;
			coordtext[tamaGeometriaCoordText - numTapas].t = 0.5;
		}
		if (flagTopTape) {
			coordtext[tamaGeometriaCoordText - 1].s = 0.5;
			coordtext[tamaGeometriaCoordText - 1].t = 0.5;
		}
	}

	double *modulo = new double[numPuntosPerfil - (numTapas * 2)];

	for (int j = 0; j < slices; j++) {

		double s = j * double(float(1) / float(slices - 1));

		double sumatorio = 0;

		modulo[0] = sumatorio;

		for (int i = numTapas + 1; i < numPuntosPerfil - numTapas; i++) {

			PuntosVertices p1 = geometria[(i - cambioIndice) * slices + j].vertice;
			PuntosVertices p2 = geometria[(i - cambioIndice - 1) * slices + j].vertice;

			PuntosVertices v1;
			v1.x = p1.x - p2.x;
			v1.y = p1.y - p2.y;
			v1.z = p1.z - p2.z;

			double modV1 = sqrt((v1.x * v1.x) + (v1.y * v1.y) + (v1.z * v1.z));

			sumatorio += modV1;

			modulo[i - 2] = sumatorio;
		}

		for (int i = 2; i < numPuntosPerfil - 2; i++) {

			double t = (modulo[i - 2]) / (sumatorio);

			coordtext[(i - cambioIndice) * slices + j].s = s;
			coordtext[(i - cambioIndice) * slices + j].t = t;
		}
	}

	// INDICES

	if (flagBottomTape) {
		int w = 0;
		for (int i = 0; i < slices; i++) {
			indicesBottomTape[w] = i;
			w++;
		}
		indicesBottomTape[w] = tamaGeometriaCoordText - numTapas;
	}
	if (flagTopTape) {
		int u = 0;
		for (int i = 0; i < slices; i++) {
			indicesTopTape[u] = (tamaGeometriaCoordText - numTapas - slices) + i;
			u++;
		}
		indicesTopTape[u] = tamaGeometriaCoordText - 1;
	}
	int k = 0;
	for (int i = 0; i < slices; i++) {
		for (int j = 0; j < numPuntosPerfil - ((cambioIndice - numTapas) * -2); j++) {
			indices[k] = i + (j * slices);
			indices[k + 1] = ((i + 1) % slices) + (j * slices);
			k += 2;
		}
		indices[k] = 0xFFFF;
		k++;
	}
}

void PagRevolutionObject::draw(GLFWwindow *_window, int nobejct) {
	struct PagPositionColor {
		glm::vec3 position;
		glm::vec3 color;
	};

	PagShaderProgram pepe;
	//pepe.createShaderProgram("points");
	pepe.createShaderProgram("pointsMultiColor");

	//GLfloat sizes[] = { 8.0f, 10.0f , 20.0f , 15.0f , 8.0f, 30.0f, 12.0f, 22.0f };

	/*PagPositionColor geometry[] = {

		{ glm::vec3(-1.0, -1.0, -10.0), glm::vec3(1.0, 0.0, 0.0) },
		{ glm::vec3(1.0,  -1.0, -10.0), glm::vec3(1.0, 0.0, 0.0) },
		{ glm::vec3(-1.0, 1.0, -10.0), glm::vec3(0.0, 0.0, 0.0) },
		{ glm::vec3(1.0, 1.0, -10.0), glm::vec3(0.0, 1.0, 0.0) },
		{ glm::vec3(-1.0, -1.0, -5.0), glm::vec3(0.0, 1.0, 0.0) },
		{ glm::vec3(1.0, -1.0, -5.0), glm::vec3(0.0, 0.0, 1.0) },
		{ glm::vec3(-1.0, 1.0, -5.0), glm::vec3(0.0, 0.0, 1.0) },
		{ glm::vec3(1.0, 1.0, -5.0), glm::vec3(0.0, 0.0, 0.0) },
	};*/

	/*glm::vec3 points[] = {
		glm::vec3(1.0, -1.0, -10.0),
		glm::vec3(-1.0,  1.0, -10.0),
		glm::vec3(1.0,  1.0, -10.0),
		glm::vec3(-1.0, -1.0, -5.0),
		glm::vec3(1.0, -1.0, -5.0),
		glm::vec3(-1.0,  1.0, -5.0),
		glm::vec3(1.0,  1.0, -5.0)
	};*/

	PagPositionColor *pointsColor = new PagPositionColor[tamaGeometriaCoordText];
	for (int i = 0; i < tamaGeometriaCoordText; i++) {
		pointsColor[i] = { glm::vec3((GLfloat)geometria[i].vertice.x, (GLfloat)geometria[i].vertice.y, (GLfloat)geometria[i].vertice.z),
							glm::vec3(0.0, 0.0, 0.0) };
	}

	int j = 0;
	GLuint *_indices = new GLuint[tamaIndices - slices];
	for (int i = 0; i < tamaIndices; i++) {
		if (indices[i] != 0xFFFF) {
			_indices[j] = (GLuint)indices[i];
			j++;
		}
	}

	GLuint *_indicesBottom = nullptr;
	if (flagBottomTape) {
		_indicesBottom = new GLuint[slices + 1];
		for (int i = 0; i < slices + 1; i++) {
			_indicesBottom[i] = (GLuint)indicesBottomTape[i];
			pointsColor[_indicesBottom[i]].color = glm::vec3(1.0, 0.0, 0.0);
		}
	}

	GLuint *_indicesTop = nullptr;
	if (flagTopTape) {
		_indicesTop = new GLuint[slices + 1];
		for (int i = 0; i < slices + 1; i++) {
			_indicesTop[i] = (GLuint)indicesTopTape[i];
			pointsColor[_indicesTop[i]].color = glm::vec3(0.0, 0.0, 1.0);
		}
	}

	GLuint vao;
	GLuint vbo;
	//GLuint vboSize;
	GLuint ibo;
	GLuint iboBottomTape;
	GLuint iboTopTape;

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
		((GLubyte *)nullptr + (0)));
	//MULTICOLOR
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, sizeof(glm::vec3) / sizeof(GLfloat),
		GL_FLOAT, GL_FALSE, sizeof(PagPositionColor),						//COLORS
		((GLubyte *)nullptr + (sizeof(glm::vec3))));

	//glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(PagPositionColor) * tamaGeometriaCoordText, pointsColor, GL_STATIC_DRAW);

	//glGenBuffers(1, &vboSize);
	//glBindBuffer(GL_ARRAY_BUFFER, vboSize);									//Enlazamos en nuevo vbo

	//glEnableVertexAttribArray(2);
	//glVertexAttribPointer(2, sizeof(GLfloat) / sizeof(GLfloat),
	//	GL_FLOAT, GL_FALSE, sizeof(GLfloat),						//TAMAÑOS
	//	((GLubyte *)NULL + (0)));

	//glBufferData(GL_ARRAY_BUFFER, sizeof(sizes), sizes, GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * (tamaIndices - slices), _indices, GL_STATIC_DRAW);

	if (flagBottomTape) {
		glGenBuffers(1, &iboBottomTape);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboBottomTape);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * (slices + 1), _indicesBottom, GL_STATIC_DRAW);
	}

	if (flagTopTape) {
		glGenBuffers(1, &iboTopTape);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboTopTape);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * (slices + 1), _indicesTop, GL_STATIC_DRAW);
	}

	do {
		glClear(GL_COLOR_BUFFER_BIT);
		pepe.use();
		pepe.setUniform("pointSize", 4.0f);

		glm::mat4 ProjectionMatrix = glm::mat4(1.0f);
		glm::mat4 ModelViewMatrix = glm::mat4(1.0f);
		ProjectionMatrix *= glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.f);
		ModelViewMatrix *= glm::lookAt(glm::vec3(20.0, 20.0, -20.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

		glm::mat4 ModelViewProjectionMatrix = ProjectionMatrix * ModelViewMatrix;

		//pepe.setUniform("vColor", glm::vec3(0.0f, 0.0f, 1.0f));		//No esta en el shader
		//pepe.setUniform("mvpMatrix", glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.f));

		pepe.setUniform("mvpMatrix", ModelViewProjectionMatrix);
		glBindVertexArray(vao);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glDrawElements(GL_POINTS, (sizeof(GLuint) * (tamaIndices - slices)) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);

		if (flagBottomTape) {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboBottomTape);
			glDrawElements(GL_POINTS, (sizeof(GLuint) * (slices + 1)) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
		}

		if (flagTopTape) {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboTopTape);
			glDrawElements(GL_POINTS, (sizeof(GLuint) * (slices + 1)) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
		}

		glfwSwapBuffers(_window);
		glfwPollEvents();
	} while (glfwGetKey(_window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(_window) == 0);

	delete[] pointsColor;
	delete[] _indices;
	if (flagTopTape) delete[] _indicesTop;
	if (flagBottomTape) delete[] _indicesBottom;
}

PagRevolutionObject::~PagRevolutionObject() {
	if (geometria != nullptr) delete[] geometria;
	if (coordtext != nullptr) delete[] coordtext;
	if (indices != nullptr) delete[] indices;
	if (indicesBottomTape != nullptr) delete[] indicesBottomTape;
	if (indicesTopTape != nullptr) delete[] indicesTopTape;
}
