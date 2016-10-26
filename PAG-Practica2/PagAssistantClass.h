#pragma once
#include <iostream>
#include "PagRevolutionObject.h"

class PagAssistantClass{
	PagRevolutionObject revolutionObject;
	void devolverDatos() const;
	std::string nombreAlumno;
	bool flagBottomTape;
	bool flagTopTape;
public:
	PagAssistantClass();
	PagAssistantClass(std::string archivoIN, int slices, std::string _nombreAlumno);
	PagRevolutionObject getObject() const { return revolutionObject; }
	~PagAssistantClass();
};

