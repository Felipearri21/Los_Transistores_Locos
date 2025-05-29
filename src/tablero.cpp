#include "tablero.h"
#include "peon.h"
#include "vector2d.h"
#include "reina.h"
#include "rey.h"
#include "torre.h"
#include "caballo.h"
#include "alfil.h"

Tablero::Tablero(ModoJuego modoSeleccionado) : 
    modo(modoSeleccionado), config(ModoJuegoConfig::obtenerConfigModo(modoSeleccionado)) {
    
    tamCasilla = (1080.0f * 0.7f) / config.filas;// El tamaño de la casilla se adapta según haya más o menos

    float anchoTablero = config.columnas * tamCasilla;
    float altoTablero = config.filas * tamCasilla;

    origenTablero = Vector2D{
        (1920 - anchoTablero) / 2.0f,
        (1080 - altoTablero) / 2.0f
    };
    inicializarPiezas();
}

void Tablero::dibujarTablero() {
    for (int fila = 0; fila < config.filas; ++fila) {
        for (int col = 0; col < config.columnas; ++col) {
            float x = origenTablero.x + col * tamCasilla;
            float y = origenTablero.y + fila * tamCasilla;

            // Posición centro de la casilla
            float centerX = x ;
            float centerY = y ;

            if ((fila + col) % 2 == 0) {
                casillaclara.setPos(centerX, centerY);
                casillaclara.setSize(tamCasilla, tamCasilla);
                casillaclara.draw();
            }
            else {
                casillaoscura.setPos(centerX, centerY);
                casillaoscura.setSize(tamCasilla, tamCasilla);
                casillaoscura.draw();
            }
        }
    }
}
Tablero::~Tablero() {
    for (Pieza* p : piezas)
        delete p;
}
void Tablero::dibujarPiezas() const {
    for ( Pieza* p : piezas) {
        if (p) p->dibujar();
    }
}
Vector2D Tablero::casillaAPosicion(int col, int fila) const {
    return Vector2D(
        origenTablero.x + col * tamCasilla ,
        origenTablero.y + fila * tamCasilla 
    );
}
void Tablero::inicializarPiezas() {
    piezas.clear();

    const int F = config.filas;
    const int C = config.columnas;

    if (!config.permite(TipoPieza::PEON)) return;

    for (int col = 0; col < C; ++col) {
        
        piezas.push_back(new Peon(casillaAPosicion(col, 1), true,tamCasilla));// Peones blancos (fila 1)
        piezas.push_back(new Peon(casillaAPosicion(col, F - 2), false,tamCasilla));// Peones negros (fila Final - 2)
    }
    piezas.push_back(new reina(casillaAPosicion((C / 2) - 1, 0), true, tamCasilla));
    piezas.push_back(new reina(casillaAPosicion((C / 2) - 1, F-1), false, tamCasilla));
    piezas.push_back(new rey(casillaAPosicion((C / 2), 0), true, tamCasilla));
    piezas.push_back(new rey(casillaAPosicion((C / 2), F - 1), false, tamCasilla));
    piezas.push_back(new torre(casillaAPosicion(0, 0), true, tamCasilla));
    piezas.push_back(new torre(casillaAPosicion(0, F - 1), false, tamCasilla));
    piezas.push_back(new torre(casillaAPosicion(C-1, 0), true, tamCasilla));
    piezas.push_back(new torre(casillaAPosicion(C-1, F - 1), false, tamCasilla));
    if (config.permite(TipoPieza::CABALLO))
    {
        piezas.push_back(new caballo(casillaAPosicion(1, 0), true, tamCasilla));
        piezas.push_back(new caballo(casillaAPosicion(1, F - 1), false, tamCasilla));
        piezas.push_back(new caballo(casillaAPosicion(C - 2, 0), true, tamCasilla));
        piezas.push_back(new caballo(casillaAPosicion(C - 2, F - 1), false, tamCasilla));
    }
    if (config.permite(TipoPieza::ALFIL))
    {
        piezas.push_back(new alfil(casillaAPosicion(2, 0), true, tamCasilla));
        piezas.push_back(new alfil(casillaAPosicion(2, F - 1), false, tamCasilla));
        piezas.push_back(new alfil(casillaAPosicion(C - 3, 0), true, tamCasilla));
        piezas.push_back(new alfil(casillaAPosicion(C - 3, F - 1), false, tamCasilla));
    }
}
void Tablero::manejarClick(float mouseX, float mouseY) {
    int col = static_cast<int>((mouseX - origenTablero.x) / tamCasilla);
    int fila = static_cast<int>((mouseY - origenTablero.y) / tamCasilla);

    if (col < 0 || col >= config.columnas || fila < 0 || fila >= config.filas)
        return;

    Vector2D destino = casillaAPosicion(col, fila);
    // Buscar si hay una pieza en la casilla clicada
    Pieza* piezaEnClick = nullptr;
    for (Pieza* p : piezas) {
        if (p && (p->getPosicion() - destino).modulo() < tamCasilla / 2) {
            piezaEnClick = p;
            break;
        }
    }
    if (!piezaSeleccionada) {
        // Solo permite seleccionar piezas del color del turno
        if (piezaEnClick && piezaEnClick->esPiezaBlanca() == turnoBlancas) {
            piezaSeleccionada = piezaEnClick;
            casillaSeleccionada = destino;
        }
    }
    else {
        auto movimientos = piezaSeleccionada->calcularMovimientosValidos(*this);
        bool esMovimientoValido = false;
        for (const auto& mov : movimientos) {
            if ((mov - destino).modulo() < tamCasilla / 2) {
                esMovimientoValido = true;
                break;
            }
        }
        if (esMovimientoValido) {
            // Comerse pieza alida si está permitido o comer piezas contrarias si no
            if (piezaEnClick &&
                (piezaEnClick->esPiezaBlanca() != piezaSeleccionada->esPiezaBlanca() ||
                    puedeComerseAliados())) {

                auto it = std::find(piezas.begin(), piezas.end(), piezaEnClick);
                if (it != piezas.end()) {
                    delete* it;
                    piezas.erase(it);
                }
            }
            // Mover la pieza y cambiar el turno
            piezaSeleccionada->setPosicion(destino);
            Peon* peonMovido = dynamic_cast<Peon*>(piezaSeleccionada);
            if (peonMovido) {
                int filaDestino = static_cast<int>((destino.y - origenTablero.y) / tamCasilla);

                bool promociona = (peonMovido->esPiezaBlanca() && filaDestino == getFilas() - 1) ||
                    (!peonMovido->esPiezaBlanca() && filaDestino == 0);

                if (promociona) {
                    if (modo == ModoJuego::SILVERMAN) {
                        // Guardamos posición y bando y esperamos tecla R "Reina", T "Torre"
                        esperandoPromocion = true;
                        posPromocion = destino;
                        colorPromocion = peonMovido->esPiezaBlanca();
                        auto it = std::find(piezas.begin(), piezas.end(), piezaSeleccionada);
                        if (it != piezas.end()) {
                            delete* it;
                            piezas.erase(it);
                        }
                        piezaSeleccionada = nullptr;
                        return;
                    }
                    else {
                        // Promoción directa a reina en modos distintos a silverman
                        Vector2D pos = peonMovido->getPosicion();
                        bool esBlanca = peonMovido->esPiezaBlanca();
                        auto it = std::find(piezas.begin(), piezas.end(), piezaSeleccionada);
                        if (it != piezas.end()) {
                            delete* it;
                            piezas.erase(it);
                        }
                        piezas.push_back(new reina(pos, esBlanca, tamCasilla));
                        piezaSeleccionada = nullptr;
                        turnoBlancas = !turnoBlancas;
                        return;
                    }
                }
            }
            piezaSeleccionada = nullptr;
            turnoBlancas = !turnoBlancas;  // CAMBIO DE TURNO
        }
        else if (piezaEnClick && piezaEnClick->esPiezaBlanca() == turnoBlancas) {
            // Cambiar selección si haces clic en otra pieza propia
            piezaSeleccionada = piezaEnClick;
            casillaSeleccionada = destino;
        }
    }
}

void Tablero::promocionarPeon(char opcion) {
    if (!esperandoPromocion) return;

    if (opcion == 'r' || opcion == 'R') {
        piezas.push_back(new reina(posPromocion, colorPromocion, tamCasilla));
    }
    else if (opcion == 't' || opcion == 'T') {
        piezas.push_back(new torre(posPromocion, colorPromocion, tamCasilla));
    }

    esperandoPromocion = false;
    turnoBlancas = !turnoBlancas;
}

bool Tablero::estaLibre(int col, int fila) const {
    Vector2D centro = casillaAPosicion(col, fila);
    for (auto* p : piezas)
        if (p && (p->getPosicion() - centro).modulo() < tamCasilla / 2)
            return false;
    return true;
}

bool Tablero::hayPiezaContraria(int col, int fila, bool blanca) const {
    Vector2D centro = casillaAPosicion(col, fila);
    for (auto* p : piezas)
        if (p && (p->getPosicion() - centro).modulo() < tamCasilla / 2 && p->esPiezaBlanca() != blanca)
            return true;
    return false;
}

void Tablero::toggleCapturaAliados() {
    config.puedeComerseAliados = !config.puedeComerseAliados;
}

bool Tablero::puedeMoverA(int col, int fila, bool esBlanca) const {
    if (estaLibre(col, fila)) return true;

    if (hayPiezaContraria(col, fila, esBlanca)) return true;

    // Si hay una pieza aliada y está activado el modo de captura de aliados
    if (puedeComerseAliados()) {
        Vector2D centro = casillaAPosicion(col, fila);
        for (auto* p : piezas)
            if (p && (p->getPosicion() - centro).modulo() < tamCasilla / 2 && p->esPiezaBlanca() == esBlanca)
                return true;
    }

    return false;
}