#pragma once
#include <iostream>

#include "Structs.h"

#include <GL/glew.h> //glew SIEMPRE va antes del glfw
#include <GLFW/glfw3.h>

using namespace Structs;

class PagSubdivisionProfile{
private:
	PuntosPerfil* perfilOriginal;
	PuntosPerfil* perfilSubdividido;
	int numDivisiones;
	int numPuntosPerfilOriginal;
	int numPuntosPerfilSubdividido;
public:
	PagSubdivisionProfile();
	PagSubdivisionProfile(int _numPuntosPerfilOriginal, int _numDivisiones, PuntosPerfil& _perfilOriginal);
	void operator = (const PagSubdivisionProfile &orig);
	void subdivisionPolilineas();
	PuntosPerfil& getPerfil() const { return *perfilSubdividido; }
	int getNumPuntosPerfil() const { return numPuntosPerfilSubdividido; }
	~PagSubdivisionProfile();
};

