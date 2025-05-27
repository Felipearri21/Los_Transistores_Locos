#include "tablero.h"
#include "peon.h"
#include "vector2d.h"
#include "reina.h"
#include "rey.h"
#include "torre.h"
#include "caballo.h"
#include "alfil.h"

Tablero::Tablero(ModoJuego modoSeleccionado) : 
    modo(modoSeleccionado), config(ModoJuegoConfig::obtenerConfigModo(modoSeleccionado)) {
    
    tamCasilla = (1080.0f * 0.7f) / config.filas;// El tamaño de la casilla se adapta según haya más o menos

    float anchoTablero = config.columnas * tamCasilla;
    float altoTablero = config.filas * tamCasilla;

    origenTablero = Vector2D{
        (1920 - anchoTablero) / 2.0f,
        (1080 - altoTablero) / 2.0f
    };
    inicializarPiezas();
}

void Tablero::dibujarTablero() {
    for (int fila = 0; fila < config.filas; ++fila) {
        for (int col = 0; col < config.columnas; ++col) {
            float x = origenTablero.x + col * tamCasilla;
            float y = origenTablero.y + fila * tamCasilla;

            // Posición centro de la casilla
            float centerX = x + tamCasilla / 2;
            float centerY = y + tamCasilla / 2;

            if ((fila + col) % 2 == 0) {
                casillaclara.setPos(centerX, centerY);
                casillaclara.setSize(tamCasilla, tamCasilla);
                casillaclara.draw();
            }
            else {
                casillaoscura.setPos(centerX, centerY);
                casillaoscura.setSize(tamCasilla, tamCasilla);
                casillaoscura.draw();
            }
        }
    }
}
Tablero::~Tablero() {
    for (Pieza* p : piezas)
        delete p;
}
void Tablero::dibujarPiezas() const {
    for ( Pieza* p : piezas) {
        if (p) p->dibujar();
    }
}
Vector2D Tablero::casillaAPosicion(int col, int fila) const {
    return Vector2D(
        origenTablero.x + col * tamCasilla + tamCasilla / 2,
        origenTablero.y + fila * tamCasilla + tamCasilla / 2
    );
}
void Tablero::inicializarPiezas() {
    piezas.clear();

    const int F = config.filas;
    const int C = config.columnas;

    if (!config.permite(TipoPieza::PEON)) return;

    for (int col = 0; col < C; ++col) {
        
        piezas.push_back(new Peon(casillaAPosicion(col, 1), true,tamCasilla));// Peones blancos (fila 1)
        piezas.push_back(new Peon(casillaAPosicion(col, F - 2), false,tamCasilla));// Peones negros (fila Final - 2)
    }
    piezas.push_back(new reina(casillaAPosicion((C / 2) - 1, 0), true, tamCasilla));
    piezas.push_back(new reina(casillaAPosicion((C / 2) - 1, F-1), false, tamCasilla));
    piezas.push_back(new rey(casillaAPosicion((C / 2), 0), true, tamCasilla));
    piezas.push_back(new rey(casillaAPosicion((C / 2), F - 1), false, tamCasilla));
    piezas.push_back(new torre(casillaAPosicion(0, 0), true, tamCasilla));
    piezas.push_back(new torre(casillaAPosicion(0, F - 1), false, tamCasilla));
    piezas.push_back(new torre(casillaAPosicion(C-1, 0), true, tamCasilla));
    piezas.push_back(new torre(casillaAPosicion(C-1, F - 1), false, tamCasilla));
    if (config.permite(TipoPieza::CABALLO))
    {
        piezas.push_back(new caballo(casillaAPosicion(1, 0), true, tamCasilla));
        piezas.push_back(new caballo(casillaAPosicion(1, F - 1), false, tamCasilla));
        piezas.push_back(new caballo(casillaAPosicion(C - 2, 0), true, tamCasilla));
        piezas.push_back(new caballo(casillaAPosicion(C - 2, F - 1), false, tamCasilla));
    }
    if (config.permite(TipoPieza::ALFIL))
    {
        piezas.push_back(new alfil(casillaAPosicion(2, 0), true, tamCasilla));
        piezas.push_back(new alfil(casillaAPosicion(2, F - 1), false, tamCasilla));
        piezas.push_back(new alfil(casillaAPosicion(C - 3, 0), true, tamCasilla));
        piezas.push_back(new alfil(casillaAPosicion(C - 3, F - 1), false, tamCasilla));
    }
}