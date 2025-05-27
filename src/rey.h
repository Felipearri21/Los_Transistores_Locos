#pragma once
#include "ETSIDI.h"
#include "freeglut.h"
#include "pieza.h"

class rey : public Pieza {
public:
    ETSIDI::Sprite spriteclaro{ "imagenes/reyclaro1.png",5 };
    ETSIDI::Sprite spriteoscuro{ "imagenes/reyoscuro1.png",5 };
    rey(Vector2D pos, bool blanca, float tamCasilla);

    void dibujar()  override;
    std::vector<Vector2D> calcularMovimientosValidos(const Tablero& tablero) const override;

};


