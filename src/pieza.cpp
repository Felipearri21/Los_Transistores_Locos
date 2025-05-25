#include "pieza.h"

Pieza::Pieza(Vector2D pos, bool blanca, TipoPieza tipoPieza)
    : posicion(pos), esBlanca(blanca), tipo(tipoPieza), destino(pos), velocidad({ 0, 0 }) {
}