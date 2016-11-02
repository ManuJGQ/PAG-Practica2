#include "Pag3DGroup.h"
#include "Pag3DObject.h"

void Pag3DGroup::drawPointsCloud() {
	for (int i = 0; i < numObjects; i++) {
		elements[i]->drawPointsCloud();
	}
}

Pag3DGroup::Pag3DGroup(): elements(nullptr), numObjects(0) {
	ModelMatrix = glm::mat4(1.0f);
}

Pag3DGroup::Pag3DGroup(Structs::Fichero ficheros[], int _numObjects) : numObjects(_numObjects) {
	ModelMatrix = glm::mat4(1.0f);
	elements = new Pag3DElement*[numObjects];
	for (int i = 0; i < numObjects; i++) {
		elements[i] = new Pag3DObject(ficheros[i]);
	}
}

Pag3DGroup::Pag3DGroup(Pag3DGroup groups[], int _numObjects): numObjects(0) {
	ModelMatrix = glm::mat4(1.0f);
	elements = new Pag3DElement*[_numObjects];
	for (int i = 0; i < _numObjects; i++) { elements[i] = new Pag3DGroup(groups[i]); }
}

Pag3DGroup::Pag3DGroup(const Pag3DGroup& orig) : numObjects(orig.numObjects) {
	ModelMatrix = glm::mat4(1.0f);
	ModelMatrix *= orig.ModelMatrix;
	elements = new Pag3DElement*[numObjects];
	for (int i = 0; i < numObjects; i++) {
		Pag3DObject* object = dynamic_cast<Pag3DObject*>(orig.elements[i]);
		if(object != nullptr) {
			elements[i] = new Pag3DObject(*object);
		}
	}
}

void Pag3DGroup::operator=(const Pag3DGroup& orig) {
	ModelMatrix = glm::mat4(1.0f);
	ModelMatrix *= orig.ModelMatrix;
	numObjects = orig.numObjects;
	elements = new Pag3DElement*[numObjects];
	for (int i = 0; i < numObjects; i++) {
		Pag3DObject* object = dynamic_cast<Pag3DObject*>(orig.elements[i]);
		if (object != nullptr) {
			elements[i] = new Pag3DObject(*object);
		}
	}
}

void Pag3DGroup::createObject(){
	for (int i = 0; i < numObjects; i++) {
		elements[i]->createObject();
	}
}

Pag3DGroup::~Pag3DGroup() {
	for (int i = 0; i < numObjects; i++) {
		delete elements[i];
	}
	delete[] elements;
}
