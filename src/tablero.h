#pragma once
#include "ETSIDI.h"
#include "freeglut.h"
#include "modojuego.h"
#include "vector2d.h"
#include <vector>
#include "pieza.h"
#include "peon.h"
#include <iostream>

class Tablero {
private:
    ModoJuego modo;
    ModoJuegoConfig config;
    float tamCasilla;
    Vector2D origenTablero;
    bool esperandoPromocion = false;
    bool gameOver = false;
    Vector2D posPromocion;
    bool colorPromocion;
    std::string mensajeFinal;

    std::vector<Pieza*> piezas;
    void inicializarPiezas();
    bool turnoBlancas = true;
    bool hayJaqueBlancas = false;
    bool hayJaqueNegras = false;
    void toggleCapturaAliados();

public:
    Vector2D casillaAPosicion(int col, int fila) const;
    Pieza* piezaSeleccionada = nullptr;
    Vector2D casillaSeleccionada;
    ETSIDI::Sprite casillaclara{ "imagenes/cuadrado.png",5 };
    ETSIDI::Sprite casillaoscura{ "imagenes/cuadrado2.png",5 };
    ETSIDI::Sprite jaquenegras{ "imagenes/jaqueN.png",1 };
    ETSIDI::Sprite jaqueblancas{ "imagenes/jaqueB.png",1 };
    ETSIDI::Sprite ImagJaqueMate{ "imagenes/JaqueM.png",1 };
    Tablero(ModoJuego modoSeleccionado);
    Tablero clonar() const;
    void dibujarTablero();
    void dibujarPiezas() const;
    void dibujarJaque();
    void manejarClick(float mouseX, float mouseY);
    void promocionarPeon(char opcion);
    int getFilas() const { return config.filas; }
    int getColumnas() const { return config.columnas; }
    bool puedeComerseAliados() const { return config.puedeComerseAliados; }
    const std::vector<TipoPieza>& getPiezasPermitidas() const { return config.piezasPermitidas; }
    Vector2D getOrigen() const { return origenTablero; }
    float getTamCasilla() const { return tamCasilla; }
    bool estaLibre(int col, int fila) const;
    bool hayPiezaContraria(int col, int fila, bool blanca) const;
    bool puedeMoverA(int col, int fila, bool esBlanca) const;
    friend void OnKeyboard(unsigned char key, int x, int y);
    bool Jaque(bool esBlancas);
    void simularMovimiento(Pieza* pieza, Vector2D destino);
    bool JaqueMate(bool esBlancas);
    ~Tablero();
    bool estaTerminado() const { return gameOver; }
    const std::string& getMensajeFinal() const { return mensajeFinal; }
};