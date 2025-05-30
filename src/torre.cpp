 #include "torre.h"
#include "tablero.h"

torre::torre(Vector2D pos, bool blanca, float tamCasilla)
    : Pieza(pos, blanca, TipoPieza::TORRE) {

    //Calculo de cual tamaño es necesario
    if (tamCasilla >= 130)  // por ejemplo para modo NORMAL
        if (esBlanca) {
            spriteclaro = { "imagenes/torreclarasilverman.png",5 };
            spriteclaro.setPos(pos.x, pos.y);
        }
        else {
            spriteoscuro = { "imagenes/torreoscurasilverman.png",5 };
            spriteoscuro.setPos(pos.x, pos.y);
        }
    else if (tamCasilla >= 100)  // por ejemplo ALAMOS
        if (esBlanca) {
            spriteclaro = { "imagenes/torreclaraalamos.png",5 };
            spriteclaro.setPos(pos.x, pos.y);
        }
        else {
            spriteoscuro = { "imagenes/torreoscuraalamos.png",5 };
            spriteoscuro.setPos(pos.x, pos.y);
        }
    else {
        if (esBlanca) {
            spriteclaro = { "imagenes/torreclara1.png",5 };
            spriteclaro.setPos(pos.x, pos.y);
        }
        else {
            spriteoscuro = { "imagenes/torreoscura1.png",5 };
            spriteoscuro.setPos(pos.x, pos.y);
        }
    }
}

void torre::dibujar() {

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

std::vector<Vector2D> torre::calcularMovimientosValidos(const Tablero& tablero) const {
    std::vector<Vector2D> movimientos;

    int col = static_cast<int>((posicion.x - tablero.getOrigen().x) / tablero.getTamCasilla());
    int fila = static_cast<int>((posicion.y - tablero.getOrigen().y) / tablero.getTamCasilla());

    // Direcciones en línea recta: arriba, abajo, izquierda, derecha
    int dir[4][2] = {
        {-1, 0}, // arriba
        {1, 0},  // abajo
        {0, -1}, // izquierda
        {0, 1}   // derecha
    };

    for (int d = 0; d < 4; ++d) {
        int f = fila + dir[d][0];
        int c = col + dir[d][1];

        while (f >= 0 && f < tablero.getFilas() && c >= 0 && c < tablero.getColumnas()) {
            if (tablero.puedeMoverA(c, f, esBlanca)) {
                movimientos.push_back(tablero.casillaAPosicion(c, f));
                if (!tablero.estaLibre(c, f)) break;
            }
            else {
                break;
            }
            f += dir[d][0];
            c += dir[d][1];
        }
    }

    return movimientos;
}
Pieza* torre::clonar() const { 
    return new torre(*this); 
}