#pragma once
#include "ETSIDI.h"
#include "freeglut.h"
#include "modojuego.h"
#include "vector2d.h"
#include <vector>
#include "pieza.h"
#include "peon.h"

class Tablero {
private:
    ModoJuego modo;
    ModoJuegoConfig config;
    float tamCasilla;
    Vector2D origenTablero;

    std::vector<Pieza*> piezas;
    void inicializarPiezas();
    bool turnoBlancas = true;

public:
    Vector2D casillaAPosicion(int col, int fila) const;
    Pieza* piezaSeleccionada = nullptr;
    Vector2D casillaSeleccionada;
    ETSIDI::Sprite casillaclara{ "imagenes/cuadrado.png",5 };
    ETSIDI::Sprite casillaoscura{ "imagenes/cuadrado2.png",5 };
    Tablero(ModoJuego modoSeleccionado);
    void dibujarTablero();
    void dibujarPiezas() const;
    void manejarClick(float mouseX, float mouseY);
    int getFilas() const { return config.filas; }
    int getColumnas() const { return config.columnas; }
    bool puedeComerseAliados() const { return config.puedeComerseAliados; }
    const std::vector<TipoPieza>& getPiezasPermitidas() const { return config.piezasPermitidas; }
    Vector2D getOrigen() const { return origenTablero; }
    float getTamCasilla() const { return tamCasilla; }
    bool estaLibre(int col, int fila) const;
    bool hayPiezaContraria(int col, int fila, bool blanca) const;
    ~Tablero();
};