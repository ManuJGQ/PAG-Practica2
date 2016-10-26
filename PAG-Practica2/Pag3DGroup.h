#pragma once

#include "Structs.h"
#include "Pag3DElement.h"

class Pag3DGroup : public Pag3DElement {
	Pag3DElement** elements;
	int numFicheros;
public:
	void draw() override;
	Pag3DGroup(Structs::Fichero ficheros[], int _numFicheros);
	~Pag3DGroup();
};

