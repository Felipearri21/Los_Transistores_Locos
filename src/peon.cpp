#include "peon.h"
#include "tablero.h"
#include "vector2d.h"
Peon::Peon(Vector2D pos, bool blanca,float tamCasilla)
    : Pieza(pos, blanca, TipoPieza::PEON) {

    //Calculo de cual tamaño es necesario
    if (tamCasilla >= 130)  // por ejemplo para modo NORMAL
        if (esBlanca) {
            spriteclaro={ "imagenes/peonclarosilverman.png",5 };
            spriteclaro.setCenter(pos.x, pos.y);
        }
        else {
            spriteoscuro = { "imagenes/peonoscurosilverman.png",5 };
            spriteoscuro.setCenter(pos.x, pos.y);
        }
    else if (tamCasilla >= 100)  // por ejemplo ALAMOS
        if (esBlanca) {
            spriteclaro={ "imagenes/peonclaroalamos.png",5 };
            spriteclaro.setCenter(pos.x, pos.y);
        }
        else {
            spriteoscuro ={ "imagenes/peonoscuroalamos.png",5 };
            spriteoscuro.setCenter(pos.x, pos.y);
        }
    else {
        if (esBlanca) {
            spriteclaro ={ "imagenes/peonclaro1.png",5 };
            spriteclaro.setCenter(pos.x, pos.y);
        }
        else {
            spriteoscuro ={ "imagenes/peonoscuro1.png",5 };
            spriteoscuro.setCenter(pos.x, pos.y);
        }
    }
}

void Peon::dibujar()  {
    
    // Actualiza la posición por si se ha movido
    if (esBlanca) {
        spriteclaro.setCenter(posicion.x,posicion.y);
        spriteclaro.draw();
    }
    else {
        spriteoscuro.setPos(posicion.x, posicion.y);
        spriteoscuro.draw();
    }

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