#include "peon.h"
#include "tablero.h"

Peon::Peon(Vector2D pos, bool blanca)
    : Pieza(pos, blanca, TipoPieza::PEON) {
}

// Dibujo simple del peón, hay que reemplazarlo con una imagen de un peón
void Peon::dibujar() const {
    float radio = 20.0f;
    glColor3f(esBlanca ? 1.0f : 0.0f, esBlanca ? 1.0f : 0.0f, esBlanca ? 1.0f : 0.0f); // blanco o negro

    glBegin(GL_POLYGON);
    for (int i = 0; i < 20; ++i) {
        float theta = 2.0f * 3.14159f * float(i) / float(20);
        float dx = radio * cosf(theta);
        float dy = radio * sinf(theta);
        glVertex2f(posicion.x + dx, posicion.y + dy);
    }
    glEnd();
}

// Movimiento vertical + captura diagonal
std::vector<Vector2D> Peon::calcularMovimientosValidos(const Tablero& tablero) const {
    std::vector<Vector2D> movimientos;

    int direccion = esBlanca ? 1 : -1;

    int filaActual = static_cast<int>(posicion.y);
    int colActual = static_cast<int>(posicion.x);

    int filaAvance = filaActual + direccion;

    if (tablero.getFilas() > filaAvance && filaAvance >= 0) {
        // Movimiento recto 1 casilla
        movimientos.push_back(Vector2D(colActual, filaAvance));

        // Movimiento inicial doble si está en fila base (opcional según modo)
        if ((esBlanca && filaActual == 1) || (!esBlanca && filaActual == tablero.getFilas() - 2)) {
            movimientos.push_back(Vector2D(colActual, filaAvance + direccion));
        }

        // Captura en diagonal (izquierda y derecha)
        for (int dx : {-1, 1}) {
            int nuevaCol = colActual + dx;
            if (nuevaCol >= 0 && nuevaCol < tablero.getColumnas()) {
                movimientos.push_back(Vector2D(nuevaCol, filaAvance));
            }
        }
    }

    return movimientos;
}