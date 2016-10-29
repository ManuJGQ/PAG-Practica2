#pragma once

#include "Pag3DElement.h"
#include "Structs.h"
#include "PagAssistantClass.h"

class Pag3DObject : public Pag3DElement {
	PagAssistantClass lectorDatos;
	PagRevolutionObject object;
public:
	void draw() override;
	Pag3DObject(Structs::Fichero fichero);
	Pag3DObject(const Pag3DObject &orig);
	void createObject();
	~Pag3DObject();
};

