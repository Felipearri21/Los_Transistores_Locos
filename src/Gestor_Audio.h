#pragma once

// INCLUSION DE FICHEROS Y LIBRERIAS //

// Librerias Estandar //
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

// Libreria ETSIDI //
#include "ETSIDI.h"

// Ficheros Locales //

#include "Menu.h"

// DECLARACION DE CLASE GESTOR AUDIO (Se necesita para el compilador)//

enum class Estado_Menu;

// DECLARACION DE LA ESTRUCTURA CANCION //

struct Cancion
{
    std::string nombre_Cancion;
    std::string ruta_Cancion;
    int duracion_Cancion;

    Cancion(const std::string& nombre, const std::string& ruta, int duracion)
        : nombre_Cancion(nombre), ruta_Cancion(ruta), duracion_Cancion(duracion) {
    }
};

// DECLARACION DE LA CLASE GESTOR AUDIO //


class Gestor_Audio
{

public:

	// METODOS PUBLICOS DE LA CLASE //

	// Constructor //

    static void set_Gestor_Audio();

	// Metodos de la Clase //

    static void set_Volumen(int volumen);

    static void update_Musica(Estado_Menu estado);

    static void next_Track();
    static void previous_Track();

    static void stop_Musica();
    static void pause_Musica();

    static void play_Title_Screen_Music();

    static int get_current_Track();
    static std::string get_current_Track_Name();

private:

	// PARAMETROS PRIVADOS DE LA CLASE //

    static std::vector<Cancion> v_playlist_Musica;
    static int current_Track;
    static bool playing_Musica;
    static bool paused_Track;
    static time_t track_Start_Time;
    static bool usuario_Ha_Cambiado_Pista;
    static bool reproducirAleatoria_Pendiente;  // ← Declaración necesaria para cambiar canción tras detener
    static void play_Music(const std::string& track, bool repeat = true);
    static void random_Track();
};
