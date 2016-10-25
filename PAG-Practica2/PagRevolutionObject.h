#include <iostream>
#include "PagSubdivisionProfile.h"

class PagRevolutionObject{
	bool flagBottomTape;
	bool flagTopTape;
	PagSubdivisionProfile subdivisionProfiles;
	Geometria *geometria;
	CoordTexturas *coordtext;
	int *indices;
	int *indicesBottomTape;
	int *indicesTopTape;
	void revolution();
	int slices;
	int tamaGeometriaCoordText;
	int tamaIndices;
public:
	PagRevolutionObject();
	PagRevolutionObject(int _numPuntosPerfilOriginal, int _numDivisiones, PuntosPerfil& _perfilOriginal,
		bool _flagBottomTape, bool _flagTopTape, int _slices);
	Geometria& getGeometria() const { return *geometria; }
	CoordTexturas& getCoordText() const { return *coordtext; }
	int& getIndices() const { return *indices; }
	int& getIndicesBottomTape() const { return *indicesBottomTape; }
	int& getIndicesTopTape() const { return *indicesTopTape; }
	int getTamaGeometriaCoordText() const { return tamaGeometriaCoordText; }
	int getTamaIndices() const { return tamaIndices; }
	int getTamaIndicesTapes() const { return slices + 1; }
	~PagRevolutionObject();
};

