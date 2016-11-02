#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h> //glew SIEMPRE va antes del glfw
#include <GLFW/glfw3.h>
#include "gtc\matrix_transform.hpp"

#include "PagShaderProgram.h"

#include "PagSubdivisionProfile.h"
#include "Pag3DObject.h"

class PagRevolutionObject: public Pag3DObject{
	PagShaderProgram shader;
	glm::mat4 ModelMatrix;

	bool flagBottomTape;
	bool flagTopTape;
	Geometria *geometria;
	CoordTexturas *coordtext;
	int *indices;
	int *indicesBottomTape;
	int *indicesTopTape;
	int slices;
	int tamaGeometriaCoordText;
	int tamaIndices;
	PagPositionColor *pointsColor;
	GLuint *_indices;
	GLuint *_indicesTop;
	GLuint *_indicesBottom;

	bool shaderCreado;

	std::string nombreAlumno;
public:
	PagSubdivisionProfile subdivisionProfiles;
	PagRevolutionObject();
	PagRevolutionObject(int _numPuntosPerfilOriginal, int _numDivisiones, PuntosPerfil& _perfilOriginal,
		bool _flagBottomTape, bool _flagTopTape, int _slices);
	PagRevolutionObject(Structs::Fichero _fichero);
	void operator = (const PagRevolutionObject &orig);
	void createObject() override;
	void drawPointsCloud(glm::mat4 _ViewProjectionMatrix) override;
	Geometria& getGeometria() const { return *geometria; }
	CoordTexturas& getCoordText() const { return *coordtext; }
	int& getIndices() const { return *indices; }
	int& getIndicesBottomTape() const { return *indicesBottomTape; }
	int& getIndicesTopTape() const { return *indicesTopTape; }
	int getTamaGeometriaCoordText() const { return tamaGeometriaCoordText; }
	int getTamaIndices() const { return tamaIndices; }
	int getTamaIndicesTapes() const { return slices + 1; }
	bool getFlagBottomTape() const { return flagBottomTape; }
	bool getFlagTopTape() const { return flagTopTape; }
	~PagRevolutionObject();
};

