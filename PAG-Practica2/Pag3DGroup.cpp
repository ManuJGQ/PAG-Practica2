#include "Pag3DGroup.h"
#include "Pag3DObject.h"

void Pag3DGroup::draw(GLFWwindow *_window, int nobject) {
	for (int i = 0; i < numFicheros; i++) {
		elements[i]->draw(_window, i * 2);
	}
}

Pag3DGroup::Pag3DGroup(): elements(nullptr), numFicheros(0) {}

Pag3DGroup::Pag3DGroup(Structs::Fichero ficheros[], int _numFicheros) : numFicheros(_numFicheros) {
	std::cout << "ENTRO" << std::endl;
	elements = new Pag3DElement*[numFicheros];
	for (int i = 0; i < numFicheros; i++) {
		elements[i] = new Pag3DObject(ficheros[i]);
	}
}

Pag3DGroup::Pag3DGroup(Pag3DGroup groups[], int _numGroups): numFicheros(0) {
	elements = new Pag3DElement*[_numGroups];
	for (int i = 0; i < _numGroups; i++) { elements[i] = new Pag3DGroup(groups[i]); }
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

void Pag3DGroup::operator=(const Pag3DGroup& orig) {
	numFicheros = orig.numFicheros;
	elements = new Pag3DElement*[numFicheros];
	for (int i = 0; i < numFicheros; i++) {
		Pag3DObject* object = dynamic_cast<Pag3DObject*>(orig.elements[i]);
		if (object != nullptr) {
			elements[i] = new Pag3DObject(*object);
		}
	}
}

void Pag3DGroup::createObject(){
	for (int i = 0; i < numFicheros; i++) {
		elements[i]->createObject();
	}
}

Pag3DGroup::~Pag3DGroup() {
	for (int i = 0; i < numFicheros; i++) {
		delete elements[i];
	}
	delete[] elements;
}
