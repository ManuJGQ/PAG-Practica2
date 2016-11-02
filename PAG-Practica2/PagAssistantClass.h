#pragma once

#include <iostream>
#include "PagRevolutionObject.h"

class PagAssistantClass{
public:
	PagAssistantClass();
	void operator = (const PagAssistantClass &orig);
	PagRevolutionObject leerDatos(Structs::Fichero _fichero);
	void devolverDatos(const PagRevolutionObject &object, std::string nombreAlumno) const;
	~PagAssistantClass();
};

