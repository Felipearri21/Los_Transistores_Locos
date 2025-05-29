#include "reina.h"
#include "tablero.h"

reina::reina(Vector2D pos, bool blanca, float tamCasilla)
    : Pieza(pos, blanca, TipoPieza::PEON) {

    //Calculo de cual tamaño es necesario
    if (tamCasilla >= 130)  // por ejemplo para modo NORMAL
        if (esBlanca) {
            spriteclaro = { "imagenes/damaclarasilverman.png",5 };
            spriteclaro.setPos(pos.x, pos.y);
        }
        else {
            spriteoscuro = { "imagenes/damaoscurasilverman.png",5 };
            spriteoscuro.setPos(pos.x, pos.y);
        }
    else if (tamCasilla >= 100)  // por ejemplo ALAMOS
        if (esBlanca) {
            spriteclaro = { "imagenes/damaclaraalamos.png",5 };
            spriteclaro.setPos(pos.x, pos.y);
        }
        else {
            spriteoscuro = { "imagenes/damaoscuraalamos.png",5 };
            spriteoscuro.setPos(pos.x, pos.y);
        }
    else {
        if (esBlanca) {
            spriteclaro = { "imagenes/damaclara1.png",5 };
            spriteclaro.setPos(pos.x, pos.y);
        }
        else {
            spriteoscuro = { "imagenes/damaoscura1.png",5 };
            spriteoscuro.setPos(pos.x, pos.y);
        }
    }
}

void reina::dibujar() {

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

std::vector<Vector2D> reina::calcularMovimientosValidos(const Tablero& tablero) const {
    std::vector<Vector2D> movimientos;

    int col = static_cast<int>((posicion.x - tablero.getOrigen().x) / tablero.getTamCasilla());
    int fila = static_cast<int>((posicion.y - tablero.getOrigen().y) / tablero.getTamCasilla());

    // 8 direcciones: vertical, horizontal y diagonal
    int dir[8][2] = {
        {-1, 0}, {1, 0},  // vertical ↑ ↓
        {0, -1}, {0, 1},  // horizontal ← →
        {-1, -1}, {-1, 1}, {1, 1}, {1, -1}  // diagonales
    };

    for (int d = 0; d < 8; ++d) {
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
