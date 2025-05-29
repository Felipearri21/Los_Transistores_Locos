#pragma once
#include "ETSIDI.h"
#include "freeglut.h"
#include "pieza.h"

class reina : public Pieza {
public:
    ETSIDI::Sprite spriteclaro{ "imagenes/damaclara1.png",5 };
    ETSIDI::Sprite spriteoscuro{ "imagenes/damaoscura1.png",5 };
    reina(Vector2D pos, bool blanca, float tamCasilla);

    void dibujar()  override;
    std::vector<Vector2D> calcularMovimientosValidos(const Tablero& tablero) const override;
    Pieza* clonar() const override;

};
