#include "Pag3DGroup.h"
#include "Pag3DObject.h"

void Pag3DGroup::draw() {}

Pag3DGroup::Pag3DGroup(Structs::Fichero ficheros[], int _numFicheros) : numFicheros(_numFicheros) {
	elements = new Pag3DElement*[numFicheros];
	for (int i = 0; i < numFicheros; i++) {
		elements[i] = new Pag3DObject(ficheros[i]);
	}
}

Pag3DGroup::Pag3DGroup(Pag3DGroup groups[], int _numGroups) {
	elements = new Pag3DElement*[_numGroups];
	for (int i = 0; i < _numGroups; i++) {
		elements[i] = new Pag3DGroup(groups[i]);
	}
}

Pag3DGroup::Pag3DGroup(const Pag3DGroup& orig) : numFicheros(orig.numFicheros) {
	elements = new Pag3DElement*[numFicheros];
	for (int i = 0; i < numFicheros; i++) {
		Pag3DObject* object = dynamic_cast<Pag3DObject*>(orig.elements[i]);
		if(object != nullptr) {
			elements[i] = new Pag3DObject(*object);
		}
	}
}

Pag3DGroup::~Pag3DGroup() {
	for (int i = 0; i < numFicheros; i++) {
		delete elements[i];
	}
	delete[] elements;
}
