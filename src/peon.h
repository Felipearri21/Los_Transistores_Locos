#pragma once
#include "ETSIDI.h"
#include "freeglut.h"
#include "pieza.h"

class peon : public pieza//hereda de pieza
{
	peon(double x, double y, char color) : pieza(x, y, color) {};

};

