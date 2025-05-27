#include "alfil.h"

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

    // TODO: Implementar la lógica real para la reina

    return movimientos;
}