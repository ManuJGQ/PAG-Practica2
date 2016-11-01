#include "Pag3DObject.h"

void Pag3DObject::draw() {
	object.draw();
}

Pag3DObject::Pag3DObject() {}

Pag3DObject::Pag3DObject(Structs::Fichero fichero) {
	lectorDatos = PagAssistantClass(fichero.archivoIN, fichero.numSlices, fichero.nombreAlumno);
	object = lectorDatos.leerDatos();
}

Pag3DObject::Pag3DObject(const Pag3DObject& orig) {
	lectorDatos = orig.lectorDatos;
	object = lectorDatos.leerDatos();
}

void Pag3DObject::operator=(const Pag3DObject& orig) {
	lectorDatos = orig.lectorDatos;
	object = lectorDatos.leerDatos();
}

void Pag3DObject::createObject() {
	object.subdivisionProfiles.subdivisionPolilineas();
	object.revolution();
	lectorDatos.devolverDatos(object);
}

Pag3DObject::~Pag3DObject() {}
