#include "tablero.h"

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

void Tablero::dibujarTablero() const {
    for (int fila = 0; fila < config.filas; ++fila) {
        for (int col = 0; col < config.columnas; ++col) {
            float x = origenTablero.x + col * tamCasilla;
            float y = origenTablero.y + fila * tamCasilla;

            if ((fila + col) % 2 == 0)
                glColor3f(1.0f, 0.9f, 0.7f); // Casilla clara
            else
                glColor3f(0.5f, 0.3f, 0.1f); // Casilla oscura

            glBegin(GL_QUADS);
            glVertex2f(x, y);
            glVertex2f(x + tamCasilla, y);
            glVertex2f(x + tamCasilla, y + tamCasilla);
            glVertex2f(x, y + tamCasilla);
            glEnd();
        }
    }
}
Tablero::~Tablero() {
    for (Pieza* p : piezas)
        delete p;
}
void Tablero::dibujarPiezas() const {
    for (const Pieza* p : piezas) {
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
        
        piezas.push_back(new Peon(casillaAPosicion(col, 1), true));// Peones blancos (fila 1)

        piezas.push_back(new Peon(casillaAPosicion(col, F - 2), false));// Peones negros (fila Final - 2)
    }
}