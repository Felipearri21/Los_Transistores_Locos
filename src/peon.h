#pragma once
#include "ETSIDI.h"
#include "freeglut.h"
#include "pieza.h"

class Peon : public Pieza {
public:
    Peon(Vector2D pos, bool blanca);

    void dibujar() const override;
    std::vector<Vector2D> calcularMovimientosValidos(const Tablero& tablero) const override;
};
