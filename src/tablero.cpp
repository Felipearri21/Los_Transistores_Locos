#include "tablero.h"
Tablero::Tablero(ModoJuego modoSeleccionado) : modo(modoSeleccionado) {
    switch (modoSeleccionado) {
    case ModoJuego::NORMAL:
        filas = columnas = 8;
        tamCasilla = 80.0f;
        break;
    case ModoJuego::ALAMOS:
        filas = columnas = 6;
        tamCasilla = 100.0f;
        break;
    case ModoJuego::SILVERMAN:
        filas = columnas = 4;
        tamCasilla = 120.0f;
        break;
    }

    float anchoTablero = columnas * tamCasilla;
    float altoTablero = filas * tamCasilla;

    // Centramos el tablero en la pantalla virtual
    origenTablero = Vector2D{
        (1920 - anchoTablero) / 2.0f,
        (1080 - altoTablero) / 2.0f
    };
}

void Tablero::dibujarTablero() const {
    for (int fila = 0; fila < filas; ++fila) {
        for (int col = 0; col < columnas; ++col) {
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