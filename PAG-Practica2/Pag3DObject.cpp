#include "Pag3DObject.h"

void Pag3DObject::draw() {
}

Pag3DObject::Pag3DObject(Structs::Fichero fichero) {
	lectorDatos = PagAssistantClass(fichero.archivoIN, fichero.numSlices, fichero.nombreAlumno);
	object = lectorDatos.getObject();
}


Pag3DObject::~Pag3DObject() {}
