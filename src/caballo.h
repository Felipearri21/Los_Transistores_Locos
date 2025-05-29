#pragma once
#include "ETSIDI.h"
#include "freeglut.h"
#include "pieza.h"

class caballo : public Pieza {
public:
    ETSIDI::Sprite spriteclaro{ "imagenes/caballoclaro1.png",5 };
    ETSIDI::Sprite spriteoscuro{ "imagenes/caballooscuro1.png",5 };
    caballo(Vector2D pos, bool blanca, float tamCasilla);

    void dibujar()  override;
    std::vector<Vector2D> calcularMovimientosValidos(const Tablero& tablero) const override;
    Pieza* clonar() const override;

};

