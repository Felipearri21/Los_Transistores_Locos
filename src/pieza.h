#pragma once
#include "ETSIDI.h"
#include "vector2d.h"
#include "modojuego.h" 
#include <vector>

class Tablero; // Declaración adelantada

class Pieza {
protected:
    Vector2D posicion;
    Vector2D velocidad;
    Vector2D destino;
    bool enMovimiento = false;

    bool esBlanca;
    TipoPieza tipo;

public:
    Pieza(Vector2D pos, bool blanca, TipoPieza tipoPieza);

    virtual ~Pieza() {}

    virtual void dibujar() const = 0;
    virtual std::vector<Vector2D> calcularMovimientosValidos(const Tablero& tablero) const = 0;

    void moverA(Vector2D nuevaPos);      // Inicia animación de movimiento
    void actualizar(double t);           // Avanza movimiento (si está en animación)

    Vector2D getPosicion() const { return posicion; }
    bool esAliada(bool blancas) const { return esBlanca == blancas; }
    TipoPieza getTipo() const { return tipo; }
    bool estaEnMovimiento() const { return enMovimiento; }
};

