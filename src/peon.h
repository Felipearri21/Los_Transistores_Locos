#pragma once
#include "ETSIDI.h"
#include "freeglut.h"
#include "pieza.h"

class Peon : public Pieza {
    ETSIDI::SpriteSequence spriteclaro{"imagenes/peonclaro1.png",5};
    ETSIDI::SpriteSequence spriteoscuro{"imagenes/peonoscuro1.png",5};
public:
    Peon(Vector2D pos, bool blanca, float tamCasilla);

    void dibujar()  override;
    std::vector<Vector2D> calcularMovimientosValidos(const Tablero& tablero) const override;

};
