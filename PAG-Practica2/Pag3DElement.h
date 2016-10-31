#pragma once

#include <GL/glew.h> //glew SIEMPRE va antes del glfw
#include <GLFW/glfw3.h>

class Pag3DElement{
public:
	virtual void draw(GLFWwindow *_window, int nobject) = 0;
	virtual void createObject() = 0;
	Pag3DElement();
	virtual ~Pag3DElement();
};

