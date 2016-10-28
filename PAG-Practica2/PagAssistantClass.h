#pragma once
#include <iostream>
#include "PagRevolutionObject.h"

class PagAssistantClass{
	PagRevolutionObject revolutionObject;
	std::string nombreAlumno;
	bool flagBottomTape;
	bool flagTopTape;
public:
	PagAssistantClass();
	PagAssistantClass(std::string archivoIN, int slices, std::string _nombreAlumno);
	void operator = (const PagAssistantClass &orig);
	void devolverDatos() const;
	PagRevolutionObject getObject() const { return revolutionObject; }
	~PagAssistantClass();
};

