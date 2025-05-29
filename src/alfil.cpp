#include "alfil.h"
#include "tablero.h"

alfil::alfil(Vector2D pos, bool blanca, float tamCasilla)
    : Pieza(pos, blanca, TipoPieza::PEON) {

    //Calculo de cual tamaño es necesario
    if (tamCasilla >= 130)  // por ejemplo para modo NORMAL
        if (esBlanca) {
            spriteclaro = { "imagenes/alfilclarosilverman.png",5 };
            spriteclaro.setPos(pos.x, pos.y);
        }
        else {
            spriteoscuro = { "imagenes/alfiloscurosilverman.png",5 };
            spriteoscuro.setPos(pos.x, pos.y);
        }
    else if (tamCasilla >= 100)  // por ejemplo ALAMOS
        if (esBlanca) {
            spriteclaro = { "imagenes/alfilclaroalamos.png",5 };
            spriteclaro.setPos(pos.x, pos.y);
        }
        else {
            spriteoscuro = { "imagenes/alfiloscuroalamos.png",5 };
            spriteoscuro.setPos(pos.x, pos.y);
        }
    else {
        if (esBlanca) {
            spriteclaro = { "imagenes/alfilclaro1.png",5 };
            spriteclaro.setPos(pos.x, pos.y);
        }
        else {
            spriteoscuro = { "imagenes/alfiloscuro1.png",5 };
            spriteoscuro.setPos(pos.x, pos.y);
        }
    }
}

void alfil::dibujar() {

    // Actualiza la posición por si se ha movido
    if (esBlanca) {
        spriteclaro.setPos(posicion.x, posicion.y);
        spriteclaro.draw();
    }
    else {
        spriteoscuro.setPos(posicion.x, posicion.y);
        spriteoscuro.draw();
    }

}

std::vector<Vector2D> alfil::calcularMovimientosValidos(const Tablero& tablero) const {
    std::vector<Vector2D> movimientos;

    int col = static_cast<int>((posicion.x - tablero.getOrigen().x) / tablero.getTamCasilla());
    int fila = static_cast<int>((posicion.y - tablero.getOrigen().y) / tablero.getTamCasilla());

    // Direcciones diagonales: {fila, col}
    int dir[4][2] = { {-1, -1}, {-1, 1}, {1, 1}, {1, -1} };

    for (int d = 0; d < 4; ++d) {
        int df = dir[d][0];
        int dc = dir[d][1];
        int f = fila + df;
        int c = col + dc;

        while (f >= 0 && f < tablero.getFilas() && c >= 0 && c < tablero.getColumnas()) {
            if (tablero.puedeMoverA(c, f, esBlanca)) {
                movimientos.push_back(tablero.casillaAPosicion(c, f));
                if (!tablero.estaLibre(c, f)) break;
            }
            else {
                break;
            }
            f += df;
            c += dc;
        }
    }

    return movimientos;
}