#pragma once

// INCLUSIÓN DE LIBRERÍAS Y FICHEROS DE CABECERA

// Inclusión de Librerías Estandar //
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

// Inclusión de Libreria de ETSIDI //
#include "ETSIDI.h"

// Inclsuión de Ficheros de Encabezado Locales //
#include "Menu.h"

// Declaración adelantada del enumerado (necesario para el compilador) //
enum class Estado_Menu;

// Estructura que representa una cancion //

struct Cancion 
{
    std::string nombre_Cancion;   // Titulo de la cancion //
    std::string ruta_Cancion;     // Ruta del archivo de audio //
    int duracion_Cancion;         // Duración de la cancion (en segundos) //

    // Constructor //
    Cancion
    (
        const std::string& nombre,
        const std::string& ruta,
        int duracion
    )
    {
		nombre_Cancion = nombre;
		ruta_Cancion = ruta;
		duracion_Cancion = duracion;
    }
};

class Gestor_Audio
{
public:
    // MÉTODOS PRINCIPALES DE LA CLASE GESTOR AUDIO

    // Inicializa el Gestor de Audio (carga la playlist y establece la semilla aleatoria) //
    static void set_Gestor_Audio();

    // Cambia el volumen del audio (stub; adaptar si ETSIDI dispone de dicha funcion) //
    static void set_Volumen(int volumen);

	// Actualiza la música del juego dependiendo del Estado del Menu actual //
    static void update_Musica(Estado_Menu estado);

    // Fuerza el cambio a la siguiente pista de audio //
    static void next_Track();

    // Fuerza el cambio a la pista anterior de audio //
    static void previous_Track();

    // Detiene la musica actual //
    static void stop_Musica();


    // Pausa la musica //
    static void pause_Musica();

    // Reproduce la musica de la pantalla de titulo //
    static void play_Title_Screen_Music();

    // Accesor para obtener el indice de la pista actual.
    static int get_current_Track();

    // Accesor para obtener el nombre de la pista actual (para mostrar en la interfaz).
    static std::string get_current_Track_Name();

private:
    // Vector de pistas de audio (almacena objetos Cancion).
    static std::vector<Cancion> v_playlist_Musica;

    // Número de la pista de audio actual (índice en el vector).
    static int current_Track;

    // Variable booleana que indica si la musica se esta reproduciendo //
    static bool playing_Musica;


    // Variable booleana que indica si la musica esta pausada //
    static bool paused_Track;

    // Guarda el tiempo de inicio de la pista actual (utilizando <ctime>).
    static time_t track_Start_Time;

    // Reproduce la pista de audio utilizando la ruta proporcionada.
    // El parámetro "repeat" indica si se debe repetir la pista.
    static void play_Music(const std::string& track, bool repeat = true);

    // Selecciona una pista aleatoria de la lista de reproducción y actualiza current_Track.
    static void random_Track();
};