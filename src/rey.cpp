#include "rey.h"
#include "tablero.h"

rey::rey(Vector2D pos, bool blanca, float tamCasilla)
    : Pieza(pos, blanca, TipoPieza::REY) {

    //Calculo de cual tamaño es necesario
    if (tamCasilla >= 130)  // por ejemplo para modo NORMAL
        if (esBlanca) {
            spriteclaro = { "imagenes/reyclarosilverman.png",5 };
            spriteclaro.setPos(pos.x, pos.y);
        }
        else {
            spriteoscuro = { "imagenes/reyoscurosilverman.png",5 };
            spriteoscuro.setPos(pos.x, pos.y);
        }
    else if (tamCasilla >= 100)  // por ejemplo ALAMOS
        if (esBlanca) {
            spriteclaro = { "imagenes/reyclaroalamos.png",5 };
            spriteclaro.setPos(pos.x, pos.y);
        }
        else {
            spriteoscuro = { "imagenes/reyoscuroalamos.png",5 };
            spriteoscuro.setPos(pos.x, pos.y);
        }
    else {
        if (esBlanca) {
            spriteclaro = { "imagenes/reyclaro1.png",5 };
            spriteclaro.setPos(pos.x, pos.y);
        }
        else {
            spriteoscuro = { "imagenes/reyoscuro1.png",5 };
            spriteoscuro.setPos(pos.x, pos.y);
        }
    }
}

void rey::dibujar() {

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

std::vector<Vector2D> rey::calcularMovimientosValidos(const Tablero& tablero) const {
    std::vector<Vector2D> movimientos;

    int col = static_cast<int>((posicion.x - tablero.getOrigen().x) / tablero.getTamCasilla());
    int fila = static_cast<int>((posicion.y - tablero.getOrigen().y) / tablero.getTamCasilla());

    // 8 direcciones alrededor del rey (una casilla en cualquier dirección)
    int dir[8][2] = {
        {-1, 0}, {1, 0},   // vertical ↑ ↓
        {0, -1}, {0, 1},   // horizontal ← →
        {-1, -1}, {-1, 1}, {1, 1}, {1, -1}  // diagonales
    };

    for (int d = 0; d < 8; ++d) {
        int f = fila + dir[d][0];
        int c = col + dir[d][1];

        if (f >= 0 && f < tablero.getFilas() && c >= 0 && c < tablero.getColumnas()) {
            if (tablero.puedeMoverA(c, f, esBlanca)) {
                movimientos.push_back(tablero.casillaAPosicion(c, f));
            }
        }
    }

    return movimientos;
}
Pieza* rey::clonar() const { 
    return new rey(*this); 
}