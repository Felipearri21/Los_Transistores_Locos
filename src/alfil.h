#pragma once
#include "ETSIDI.h"
#include "freeglut.h"
#include "pieza.h"

class alfil : public Pieza {
public:
    ETSIDI::Sprite spriteclaro{ "imagenes/alfilclaro1.png",5 };
    ETSIDI::Sprite spriteoscuro{ "imagenes/alfiloscuro1.png",5 };
    alfil(Vector2D pos, bool blanca, float tamCasilla);

    void dibujar()  override;
    std::vector<Vector2D> calcularMovimientosValidos(const Tablero& tablero) const override;
    Pieza* clonar() const override;

};