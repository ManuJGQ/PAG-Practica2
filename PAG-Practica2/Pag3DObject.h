#pragma once

#include "Pag3DElement.h"
#include "PagShaderProgram.h"
#include "Structs.h"

class Pag3DObject : public Pag3DElement {
	glm::mat4 ModelMatrix;
	PagShaderProgram shader;
public:
	void drawPointsCloud() override = 0;
	void createObject() override = 0;
	Pag3DObject();
	Pag3DObject(const Pag3DObject &orig);
	~Pag3DObject();
};

