#include "modojuego.h"

ModoJuegoConfig ModoJuegoConfig::obtenerConfigModo(ModoJuego modo) {
    switch (modo) {
    case ModoJuego::NORMAL:
        return { 8, 8, false, {TipoPieza::PEON, TipoPieza::TORRE, TipoPieza::CABALLO, TipoPieza::ALFIL, TipoPieza::REINA, TipoPieza::REY} };
    case ModoJuego::ALAMOS:
        return { 6, 6, true, {TipoPieza::PEON, TipoPieza::TORRE, TipoPieza::CABALLO, TipoPieza::REINA, TipoPieza::REY} };
    case ModoJuego::SILVERMAN:
        return { 4, 4, true, {TipoPieza::PEON, TipoPieza::TORRE, TipoPieza::REINA, TipoPieza::REY} };
    }
    return { 8, 8, false, {} }; // por defecto
}
bool ModoJuegoConfig::permite(TipoPieza tipo) const {
    for (TipoPieza p : piezasPermitidas) {
        if (p == tipo) return true;
    }
    return false;
}