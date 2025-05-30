#include <iostream>
#include "Variables_Globales.h"
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
void imprimirMensajeFinal(const std::string& mensaje, const std::string& colorCodigo) {
    std::cout << colorCodigo << mensaje << "\033[0m" << std::endl;
}

void Tablero::dibujarTablero() {
    if (gameOver) {

        float posX = origenTablero.x + config.columnas * tamCasilla;
        float posY = origenTablero.y;

        ImagJaqueMate.setPos(posX, posY);
        ImagJaqueMate.setSize(500.0f, 500.0f); // tamaño visible
        ImagJaqueMate.draw();


        return;
    }
    for (int fila = 0; fila < config.filas; ++fila) {
        for (int col = 0; col < config.columnas; ++col) {
            float x = origenTablero.x + col * tamCasilla;
            float y = origenTablero.y + fila * tamCasilla;

            // Posición centro de la casilla
            float centerX = x;
            float centerY = y;

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
    dibujarPiezas();    // Dibuja las piezas
    if (hayJaqueBlancas || hayJaqueNegras) {
        dibujarJaque();
    }
}
Tablero::~Tablero() {
    for (Pieza* p : piezas)
        delete p;
}
void Tablero::dibujarPiezas() const {
    if (gameOver) return;
    for (Pieza* p : piezas) {
        if (p) p->dibujar();
    }
}
void Tablero::dibujarJaque() {
    if (!hayJaqueBlancas && !hayJaqueNegras) return;

    float posX = origenTablero.x + config.columnas * tamCasilla + 10; // al lado derecho del tablero
    float posY = origenTablero.y;

    if (hayJaqueBlancas) {
        jaqueblancas.setPos(posX, posY);
        jaqueblancas.setSize(500.0f, 500.0f);
        jaqueblancas.draw();
    }
    if (hayJaqueNegras) {
        jaquenegras.setPos(posX, posY);
        jaquenegras.setSize(500.0f, 500.0f);
        jaquenegras.draw();
    }
}
Vector2D Tablero::casillaAPosicion(int col, int fila) const {
    return Vector2D(
        origenTablero.x + col * tamCasilla,
        origenTablero.y + fila * tamCasilla
    );
}
void Tablero::inicializarPiezas() {
    piezas.clear();

    const int F = config.filas;
    const int C = config.columnas;

    if (!config.permite(TipoPieza::PEON)) return;

    for (int col = 0; col < C; ++col) {

        piezas.push_back(new Peon(casillaAPosicion(col, 1), true, tamCasilla));// Peones blancos (fila 1)
        piezas.push_back(new Peon(casillaAPosicion(col, F - 2), false, tamCasilla));// Peones negros (fila Final - 2)
    }
    piezas.push_back(new reina(casillaAPosicion((C / 2) - 1, 0), true, tamCasilla));
    piezas.push_back(new reina(casillaAPosicion((C / 2) - 1, F - 1), false, tamCasilla));
    piezas.push_back(new rey(casillaAPosicion((C / 2), 0), true, tamCasilla));
    piezas.push_back(new rey(casillaAPosicion((C / 2), F - 1), false, tamCasilla));
    piezas.push_back(new torre(casillaAPosicion(0, 0), true, tamCasilla));
    piezas.push_back(new torre(casillaAPosicion(0, F - 1), false, tamCasilla));
    piezas.push_back(new torre(casillaAPosicion(C - 1, 0), true, tamCasilla));
    piezas.push_back(new torre(casillaAPosicion(C - 1, F - 1), false, tamCasilla));
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
    if (gameOver) return;
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

        std::vector<Vector2D> movimientosLegales;
        for (auto mov : movimientos) {
            Tablero copia = this->clonar();
            for (Pieza* p : copia.piezas) {
                if (p &&
                    p->getPosicion() == piezaSeleccionada->getPosicion() &&
                    p->getTipo() == piezaSeleccionada->getTipo() &&
                    p->esPiezaBlanca() == piezaSeleccionada->esPiezaBlanca()) {

                    copia.piezaSeleccionada = p;
                    break;
                }
            }
            copia.simularMovimiento(copia.piezaSeleccionada, mov);

            if (!copia.Jaque(piezaSeleccionada->esPiezaBlanca()))
                movimientosLegales.push_back(mov);
        }
        movimientos = movimientosLegales;

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
            ETSIDI::play("sonidos/claves.mp3");

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
                        ETSIDI::play("sonidos/panda.mp3");
                        turnoBlancas = !turnoBlancas;
                        return;
                    }
                }
            }
            bool colorTurnoAnterior = piezaEnClick ? piezaEnClick->esPiezaBlanca() : !turnoBlancas;
            piezaSeleccionada = nullptr;
            turnoBlancas = !turnoBlancas;
            bool jaqueBlancasAhora = Jaque(true);
            bool jaqueNegrasAhora = Jaque(false);
            hayJaqueBlancas = jaqueBlancasAhora;
            hayJaqueNegras = jaqueNegrasAhora;
            if (Jaque(true)) {
                std::cout << "¡Jaque a las blancas!" << std::endl;
                if (JaqueMate(true)) {
                    std::cout << "¡Jaque mate a las blancas!" << std::endl;
                    gameOver = true;
                    mensajeFinal = "¡Jaque Mate! ¡Ganan las negras!";
                    return;
                }
            }
            else if (Jaque(false)) {
                std::cout << "¡Jaque a las negras!" << std::endl;
                if (JaqueMate(false)) {
                    std::cout << "¡Jaque mate a las negras!" << std::endl;
                    gameOver = true;
                    mensajeFinal = "¡Jaque Mate! ¡Ganan las blancas!";
                    return;
                }
            }
            else {
                std::cout << "No hay jaque." << std::endl;
                hayJaqueBlancas = false;
                hayJaqueNegras = false;
            }

            if (JaqueMate(!turnoBlancas)) {
                mensajeFinal = "¡Jaque Mate! ¡Ganan las " + std::string(!turnoBlancas ? "Blancas!" : "Negras!");
                gameOver = true;
                return;
            }
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
        ETSIDI::play("sonidos/panda.mp3");
    }
    else if (opcion == 't' || opcion == 'T') {
        piezas.push_back(new torre(posPromocion, colorPromocion, tamCasilla));
        ETSIDI::play("sonidos/panda.mp3");
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
bool Tablero::Jaque(bool esBlancas) {
    Vector2D posRey;

    // 1. Buscar la posición del rey del color que se quiere comprobar
    for (Pieza* pieza : piezas) {
        if (pieza && pieza->getTipo() == TipoPieza::REY && pieza->esPiezaBlanca() == esBlancas) {
            posRey = pieza->getPosicion();
            break;
        }
    }
    // Si no se encuentra el rey (error lógico)
    if (posRey.x == 0 && posRey.y == 0) {
        std::cout << "[ERROR] Rey no encontrado para el color: " << (esBlancas ? "blanco" : "negro") << std::endl;
        return false;
    }

    // 2. Comprobar si alguna pieza enemiga puede atacar al rey
    for (Pieza* pieza : piezas) {
        if (!pieza || pieza->esPiezaBlanca() == esBlancas)
            continue; // Saltar piezas propias

        auto movs = pieza->calcularMovimientosValidos(*this);

        for (const auto& m : movs) {
            if ((m - posRey).modulo() < tamCasilla / 2)
            {
                if (esBlancas)
                    hayJaqueBlancas = true;
                else
                    hayJaqueNegras = true;
                return true;
            }
        }
    }
    if (esBlancas)
        hayJaqueBlancas = false;
    else
        hayJaqueNegras = false;

    return false;
}
void Tablero::simularMovimiento(Pieza* pieza, Vector2D destino) {
    std::cout << "Simulando movimiento de pieza tipo " << static_cast<int>(pieza->getTipo())
        << " de (" << pieza->getPosicion().x << "," << pieza->getPosicion().y << ")"
        << " a (" << destino.x << "," << destino.y << ")" << std::endl;

    // Eliminar pieza rival en destino, si existe
    auto it = std::find_if(piezas.begin(), piezas.end(), [&](Pieza* p) {
        return p && (p->getPosicion() - destino).modulo() < tamCasilla / 2 && p->esPiezaBlanca() != pieza->esPiezaBlanca();
        });
    if (it != piezas.end()) {
        std::cout << "Capturando pieza rival en destino (" << destino.x << "," << destino.y << ")" << std::endl;
        delete* it;
        piezas.erase(it);
    }

    // Mover la pieza
    pieza->setPosicion(destino);
}


bool Tablero::JaqueMate(bool esBlancas) {
    std::cout << "Entrando en JaqueMate para " << (esBlancas ? "blancas" : "negras") << std::endl;


    if (!Jaque(esBlancas))
        return false;

    for (Pieza* pieza : piezas) {
        if (pieza && pieza->esPiezaBlanca() == esBlancas) {
            auto posiblesMovs = pieza->calcularMovimientosValidos(*this);

            for (auto mov : posiblesMovs) {
                std::cout << "Probando movimiento de pieza tipo " << static_cast<int>(pieza->getTipo())
                    << " desde (" << pieza->getPosicion().x << "," << pieza->getPosicion().y << ")"
                    << " a (" << mov.x << "," << mov.y << ")" << std::endl;

                Tablero copia = this->clonar();

                copia.piezaSeleccionada = nullptr;

                // Buscar la pieza clonada equivalente en copia
                for (Pieza* p : copia.piezas) {
                    if (p &&
                        p->getPosicion().casiIgual(pieza->getPosicion()) &&
                        p->getTipo() == pieza->getTipo() &&
                        p->esPiezaBlanca() == pieza->esPiezaBlanca()) {

                        copia.piezaSeleccionada = p;
                        break;
                    }
                }

                if (!copia.piezaSeleccionada) {
                    std::cerr << "Error: piezaSeleccionada no encontrada en la copia." << std::endl;
                    continue;
                }

                copia.simularMovimiento(copia.piezaSeleccionada, mov);

                if (!copia.Jaque(esBlancas)) {
                    std::cout << "Movimiento válido para salir del jaque." << std::endl;
                    return false; // Hay movimiento que evita jaque mate
                }
            }
        }
    }

    std::cout << "No hay movimientos para salir del jaque, es jaque mate." << std::endl;
    return true;
}

Tablero Tablero::clonar() const {
    Tablero copia = *this;
    copia.piezas.clear();

    // Clonar todas las piezas
    for (Pieza* p : piezas) {
        if (p)
            copia.piezas.push_back(p->clonar());
    }

    // Actualizar piezaSeleccionada a la copia correspondiente
    if (piezaSeleccionada) {
        for (Pieza* p : copia.piezas) {
            if (p &&
                p->getPosicion().casiIgual(piezaSeleccionada->getPosicion()) &&
                p->getTipo() == piezaSeleccionada->getTipo() &&
                p->esPiezaBlanca() == piezaSeleccionada->esPiezaBlanca()) {
                copia.piezaSeleccionada = p;
                break;
            }
        }
    }
    else {
        copia.piezaSeleccionada = nullptr;
    }

    return copia;
}