#include <iostream>

namespace Structs {
	struct PuntosPerfil{
		double x;
		double y;
	};

	struct PuntosVertices {
		double x;
		double y;
		double z;
	};

	struct NormalesTangentes{
		double x;
		double y;
		double z;
	};

	struct CoordTexturas {
		double s;
		double t;
	};

	struct Geometria {
		PuntosVertices vertice;
		NormalesTangentes normal;
		NormalesTangentes tangente;
	};
}
