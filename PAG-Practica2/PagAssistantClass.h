#pragma once

#include <iostream>
#include "PagRevolutionObject.h"

class PagAssistantClass{
	std::string nombreAlumno;
	std::string archivo;
	int slices;
	bool flagBottomTape;
	bool flagTopTape;
public:
	PagAssistantClass();
	PagAssistantClass(std::string archivoIN, int slices, std::string _nombreAlumno);
	void operator = (const PagAssistantClass &orig);
	PagRevolutionObject leerDatos();
	void devolverDatos(const PagRevolutionObject &object) const;
	~PagAssistantClass();
};

