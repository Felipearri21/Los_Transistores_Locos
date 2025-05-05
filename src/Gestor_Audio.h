#pragma once

// INCLUSI�N DE LIBRER�AS Y FICHEROS DE CABECERA

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

// Inclusi�n de la librer�a ETSIDI
#include "ETSIDI.h"

// Inclusi�n de ficheros de cabecera locales
#include "Menu.h"

// Declaraci�n de la clase Estado_Menu (para el compilador) //
enum class Estado_Menu;

// DEFINICI�N DE CLASES Y ESTRUCTURAS //

// Estructura que representa una Cancion // 

struct Cancion
{
	std::string nombre_Cancion; // Nombre de la canci�n
	std::string ruta_Cancion;   // Ruta de la canci�n
};

// Clase que representa el Gestor de Audio //

class Gestor_Audio
{
public:
    // M�TODOS PRINCIPALES DE LA CLASE GESTOR AUDIO

    // Inicializa el Gestor de Audio, cargando la playlist y estableciendo la semilla
    static void set_Gestor_Audio();

    // Cambia el volumen del audio (stub; adaptar si ETSIDI dispone de dicha funci�n)
    static void set_Volumen(int volumen);

    // Actualiza la m�sica del juego dependiendo del Estado del Men�
    static void update_Musica(Estado_Menu estado);

    // Fuerza el cambio a la siguiente pista de audio //
    static void next_Track();

	// Fuerza el cambio a la anterior pista de audio //

	static void previous_Track();

    // Detiene la m�sica actual
    static void stop_Musica();

    // Reproduce la m�sica de la pantalla de t�tulo
    static void play_Title_Screen_Music();

    // Vector de pistas de audio
    static std::vector<std::string> v_playlist_Musica;

	static int get_current_Track() 
	{
		return current_Track;
	}

	static std::string get_current_Track_Name()
	{
		if (current_Track >= 0 && current_Track < static_cast<int> (v_playlist_Musica.size()))
		{
			return v_playlist_Musica[current_Track];
		}
		return "Ninguna";
	}

private:
    // PAR�METROS PRIVADOS DE LA CLASE GESTOR AUDIO

    // Canciones //

    Cancion Dama_y_Almohada{"Dama y Almohada","sonidos/Banda_Sonora/soundtrack_Dama_y_Almohada.wav"};
	Cancion Gambito_y_Furioso{ "Gambito y Furioso","sonidos/Banda_Sonora/soundtrack_Gambito_y_Furioso.wav" };
	Cancion Jaque_Over{ "Jaque Over","sonidos/Banda_Sonora/soundtrack_Jaque_Over.wav" };
	Cancion Peon_Pisando_Fino{ "Peon Pisando Fino","sonidos/Banda_Sonora/soundtrack_Peon_Pisando_Fino.wav" };
	Cancion Susurros_del_Enroque{ "Susurros del Enroque","sonidos/Banda_Sonora/soundtrack_Susurros_del_Enroque.wav" };
	Cancion Todo_por_un_5{ "Todo por un 5","sonidos/Banda_Sonora/soundtrack_Todo_por_un_5.wav" };


    // N�mero de la pista de audio actual (�ndice en el vector)
    static int current_Track;

    // Variable booleana que indica si la m�sica se est� reproduciendo
    static bool playing_Musica;

    // Reproduce la pista de audio especificada. El par�metro "repeat" indica si se debe repetir la pista.
    static void play_Music(const std::string& track, bool repeat = true);

    // Cambia a una pista aleatoria de la lista de reproducci�n
    static void random_Track();

    // Guarda el tiempo de inicio de la pista actual (utilizando <ctime>)
    static time_t track_Start_Time;
};


