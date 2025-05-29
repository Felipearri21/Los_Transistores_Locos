#include "peon.h"
#include "tablero.h"
#include "vector2d.h"

Peon::Peon(Vector2D pos, bool blanca,float tamCasilla)
    : Pieza(pos, blanca, TipoPieza::PEON) {

    //Calculo de cual tamaño es necesario
    if (tamCasilla >= 130)  // por ejemplo para modo NORMAL
        if (esBlanca) {
            spriteclaro={ "imagenes/peonclarosilverman.png",5 };
            spriteclaro.setPos(pos.x, pos.y);
        }
        else {
            spriteoscuro = { "imagenes/peonoscurosilverman.png",5 };
            spriteoscuro.setPos(pos.x, pos.y);
        }
    else if (tamCasilla >= 100)  // por ejemplo ALAMOS
        if (esBlanca) {
            spriteclaro={ "imagenes/peonclaroalamos.png",5 };
            spriteclaro.setPos(pos.x, pos.y);
        }
        else {
            spriteoscuro ={ "imagenes/peonoscuroalamos.png",5 };
            spriteoscuro.setPos(pos.x, pos.y);
        }
    else {
        if (esBlanca) {
            spriteclaro ={ "imagenes/peonclaro1.png",5 };
            spriteclaro.setPos(pos.x, pos.y);
        }
        else {
            spriteoscuro ={ "imagenes/peonoscuro1.png",5 };
            spriteoscuro.setPos(pos.x, pos.y);
        }
    }
}

void Peon::dibujar()  {
    
    // Actualiza la posición por si se ha movido
    if (esBlanca) {
        spriteclaro.setPos(posicion.x,posicion.y);
        spriteclaro.draw();
    }
    else {
        spriteoscuro.setPos(posicion.x, posicion.y);
        spriteoscuro.draw();
    }

}

std::vector<Vector2D> Peon::calcularMovimientosValidos(const Tablero& tablero) const {
    std::vector<Vector2D> movimientos;
    int direccion = esBlanca ? 1 : -1;

    Vector2D actual = getPosicion();

    // Convertir posición actual a coordenadas de casilla
    int col = static_cast<int>((actual.x - tablero.getOrigen().x) / tablero.getTamCasilla());
    int fila = static_cast<int>((actual.y - tablero.getOrigen().y) / tablero.getTamCasilla());

    // 1. Avance simple (una casilla hacia adelante)
    int nuevaFila = fila + direccion;
    if (tablero.estaLibre(col, nuevaFila)) {
        movimientos.push_back(tablero.casillaAPosicion(col, nuevaFila));

        // 2. Avance doble (solo si está en su fila inicial)
        bool filaInicial = (esBlanca && fila == 1) || (!esBlanca && fila == tablero.getFilas() - 2);
        if (filaInicial && tablero.estaLibre(col, fila + 2 * direccion))
            movimientos.push_back(tablero.casillaAPosicion(col, fila + 2 * direccion));
    }

    // 3. Capturas diagonales
    for (int dcol : {-1, 1}) {
        int nuevaCol = col + dcol;
        if (tablero.puedeMoverA(nuevaCol, nuevaFila, esBlanca) && !tablero.estaLibre(nuevaCol, nuevaFila)) {
            movimientos.push_back(tablero.casillaAPosicion(nuevaCol, nuevaFila));
        }
    }

    return movimientos;
}
Pieza* Peon::clonar() const { 
    return new Peon(*this); 
}