#pragma once
// INCLUSION DE FICHEROS Y LIBRERIAS //

// Librerias Estandar //
#include "ETSIDI.h"

// Librerias de OpenGL //
#include "freeglut.h"

// Ficheros Locales //
#include "pieza.h"

// DEFINICION DE LA CLASE CABALLO//
class Caballo : public Pieza//hereda de pieza
{
public:
	Caballo(Vector2D pos, bool blanca) : Pieza(pos, blanca, TipoPieza::CABALLO) {};

	void dibujar() override;
	std::vector<Vector2D> calcularMovimientosValidos(const Tablero& tablero) const override;
};

