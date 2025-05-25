#pragma once
#include <vector>

enum class TipoPieza { PEON, TORRE, CABALLO, ALFIL, REINA, REY };

enum class ModoJuego {
    NORMAL,     // 8x8
    ALAMOS,     // 6x6
    SILVERMAN   // 4x4
};

struct ModoJuegoConfig {
    int filas;
    int columnas;
    bool puedeComerseAliados;
    std::vector<TipoPieza> piezasPermitidas;

    bool permite(TipoPieza tipo) const;

    static ModoJuegoConfig obtenerConfigModo(ModoJuego modo);
};

