#pragma once
#include "ETSIDI.h"
#include "freeglut.h"
#include "pieza.h"
class caballo : public pieza//hereda de pieza
{
	caballo(double x, double y, char color) : pieza(x, y, color) {};
};

