#include "Pag3DObject.h"

void Pag3DObject::draw() {
}

Pag3DObject::Pag3DObject(Structs::Fichero fichero) {
	lectorDatos = PagAssistantClass(fichero.archivoIN, fichero.numSlices, fichero.nombreAlumno);
	object = lectorDatos.getObject();
}

Pag3DObject::Pag3DObject(const Pag3DObject& orig) {
	lectorDatos = orig.lectorDatos;
	object = lectorDatos.getObject();
}

void Pag3DObject::createObject() {
	object.subdivisionProfiles.subdivisionPolilineas();
	object.revolution();
	lectorDatos.setObject(object);
	lectorDatos.devolverDatos();
}

Pag3DObject::~Pag3DObject() {}
