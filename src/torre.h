#pragma once
#include "ETSIDI.h"
#include "freeglut.h"
#include "pieza.h"

class torre : public Pieza {
public:
    ETSIDI::Sprite spriteclaro{ "imagenes/torreclara1.png",5 };
    ETSIDI::Sprite spriteoscuro{ "imagenes/torreoscura1.png",5 };
    torre(Vector2D pos, bool blanca, float tamCasilla);

    void dibujar()  override;
    std::vector<Vector2D> calcularMovimientosValidos(const Tablero& tablero) const override;

};