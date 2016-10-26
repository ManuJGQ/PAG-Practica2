#include "Pag3DGroup.h"
#include "Pag3DObject.h"

void Pag3DGroup::draw() {}

Pag3DGroup::Pag3DGroup(Structs::Fichero ficheros[], int _numFicheros) : numFicheros(_numFicheros) {
	elements = new Pag3DElement*[numFicheros];
	for (int i = 0; i < numFicheros; i++) {
		elements[i] = new Pag3DObject(ficheros[i]);
	}
}

Pag3DGroup::~Pag3DGroup() {
	for (int i = 0; i < numFicheros; i++) {
		delete elements[i];
	}
	delete[] elements;
}
