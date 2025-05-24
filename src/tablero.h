#pragma once
#include "ETSIDI.h"
#include "freeglut.h"
#include "caballo.h"
#include "rey.h"
#include "reina.h"
#include "torre.h"
#include "peon.h"
#include "pieza.h"
#include "vector2d.h"

enum class ModoJuego {
    NORMAL,     // 8x8
    ALAMOS,     // 6x6
    SILVERMAN   // 4x4
};

class Tablero {
private:
    int filas;
    int columnas;
    float tamCasilla;      // Tamaño en pantalla
    ModoJuego modo;

    Vector2D origenTablero; // Esquina inferior izquierda

public:
    Tablero(ModoJuego modo);
    void dibujarTablero() const;

    int getFilas() const { return filas; }
    int getColumnas() const { return columnas; }
};