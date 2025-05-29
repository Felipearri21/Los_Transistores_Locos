#include "caballo.h"
#include "tablero.h"

caballo::caballo(Vector2D pos, bool blanca, float tamCasilla)
    : Pieza(pos, blanca, TipoPieza::PEON) {

    //Calculo de cual tamaño es necesario
    if (tamCasilla >= 130)  // por ejemplo para modo NORMAL
        if (esBlanca) {
            spriteclaro = { "imagenes/caballoclarosilverman.png",5 };
            spriteclaro.setPos(pos.x, pos.y);
        }
        else {
            spriteoscuro = { "imagenes/caballooscurosilverman.png",5 };
            spriteoscuro.setPos(pos.x, pos.y);
        }
    else if (tamCasilla >= 100)  // por ejemplo ALAMOS
        if (esBlanca) {
            spriteclaro = { "imagenes/caballoclaroalamos.png",5 };
            spriteclaro.setPos(pos.x, pos.y);
        }
        else {
            spriteoscuro = { "imagenes/caballooscuroalamos.png",5 };
            spriteoscuro.setPos(pos.x, pos.y);
        }
    else {
        if (esBlanca) {
            spriteclaro = { "imagenes/caballoclaro1.png",5 };
            spriteclaro.setPos(pos.x, pos.y);
        }
        else {
            spriteoscuro = { "imagenes/caballooscuro1.png",5 };
            spriteoscuro.setPos(pos.x, pos.y);
        }
    }
}

void caballo::dibujar() {

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

std::vector<Vector2D> caballo::calcularMovimientosValidos(const Tablero& tablero) const {
    std::vector<Vector2D> movimientos;
    static const int dfilas[] = { -2, -1, 1, 2, 2, 1, -1, -2 };
    static const int dcols[] = { 1,  2, 2, 1, -1, -2, -2, -1 };

    int col = static_cast<int>((posicion.x - tablero.getOrigen().x) / tablero.getTamCasilla());
    int fila = static_cast<int>((posicion.y - tablero.getOrigen().y) / tablero.getTamCasilla());

    for (int i = 0; i < 8; ++i) {
        int nuevaCol = col + dcols[i];
        int nuevaFila = fila + dfilas[i];

        // Asegúrate de que esté dentro del tablero
        if (nuevaCol >= 0 && nuevaCol < tablero.getColumnas() &&
            nuevaFila >= 0 && nuevaFila < tablero.getFilas()) {

            if (tablero.puedeMoverA(nuevaCol, nuevaFila, esBlanca)) {
                movimientos.push_back(tablero.casillaAPosicion(nuevaCol, nuevaFila));
            }
        }
    }

    return movimientos;
}
Pieza* caballo::clonar() const { 
    return new caballo(*this); 
}