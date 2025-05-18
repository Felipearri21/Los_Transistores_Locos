// INCLUSION DE FICHEROS Y LIBRERIAS //

// Librerias Estandar //

#include <iostream>

// Ficheros Locales //

#include "Gestor_Audio.h"


// CONDICIONES INICIALES DE LOS PARAMETROS ESTATICOS DE LA CLASE //

std::vector<Cancion> Gestor_Audio::v_playlist_Musica;
int Gestor_Audio::current_Track = -1;
bool Gestor_Audio::playing_Musica = false;
bool Gestor_Audio::paused_Track = false;
time_t Gestor_Audio::track_Start_Time = time(nullptr);
bool Gestor_Audio::usuario_Ha_Cambiado_Pista = false;
bool Gestor_Audio::reproducirAleatoria_Pendiente = false;

// METODOS DE LA CLASE GESTOR AUDIO //

void Gestor_Audio::set_Gestor_Audio()
{
    srand(static_cast<unsigned int>(time(NULL)));
    v_playlist_Musica.clear();

    v_playlist_Musica.push_back({ "Dama y Almohada", "sonidos/Banda_Sonora/soundtrack_Dama_y_Almohada.wav", 143 });
    v_playlist_Musica.push_back({ "Gambito y Furioso", "sonidos/Banda_Sonora/soundtrack_Gambito_y_Furioso.wav", 159 });
    v_playlist_Musica.push_back({ "Jaque Over", "sonidos/Banda_Sonora/soundtrack_Jaque_Over.wav", 95 });
    v_playlist_Musica.push_back({ "Peon Pisando Fino", "sonidos/Banda_Sonora/soundtrack_Peon_Pisando_Fino.wav", 160 });
    v_playlist_Musica.push_back({ "Susurros del Enroque", "sonidos/Banda_Sonora/soundtrack_Susurros_del_Enroque.wav", 130 });
    v_playlist_Musica.push_back({ "Todo por un 5", "sonidos/Banda_Sonora/soundtrack_Todo_por_un_5.wav", 129 });

    usuario_Ha_Cambiado_Pista = false;
    reproducirAleatoria_Pendiente = false;
    current_Track = -2;
}


void Gestor_Audio::play_Music(const std::string& track, bool repeat)
{
    ETSIDI::stopMusica(); // Asegura que no hay pista previa
    ETSIDI::playMusica(track.c_str(), repeat);
    playing_Musica = true;
    paused_Track = false;
}

void Gestor_Audio::random_Track()
{
    if (v_playlist_Musica.empty()) return;

    int nuevo_Indice = current_Track;
    while (nuevo_Indice == current_Track) 
    {
        nuevo_Indice = rand() % static_cast<int>(v_playlist_Musica.size());
    }
    current_Track = nuevo_Indice;
    usuario_Ha_Cambiado_Pista = true;
    play_Music(v_playlist_Musica[current_Track].ruta_Cancion, false);
    track_Start_Time = time(nullptr);
    std::cout << "Reproduciendo aleatoria: " << v_playlist_Musica[current_Track].nombre_Cancion << std::endl;
}

void Gestor_Audio::update_Musica(Estado_Menu estado)
{
    bool en_menu = (estado == Estado_Menu::TITLE_SCREEN || estado == Estado_Menu::MAIN_MENU || estado == Estado_Menu::SETTINGS);
    bool en_juego = (estado == Estado_Menu::AJEDREZ || estado == Estado_Menu::ALAMOS || estado == Estado_Menu::SILVERMAN);

    if (en_menu)
    {
        reproducirAleatoria_Pendiente = false;

        if (!playing_Musica)
        {
            if (!usuario_Ha_Cambiado_Pista) {
                play_Title_Screen_Music();
            }
            else if (current_Track >= 0 && current_Track < (int)v_playlist_Musica.size()) {
                play_Music(v_playlist_Musica[current_Track].ruta_Cancion, false);
                track_Start_Time = time(nullptr);
            }
        }

        else
        {
            time_t tiempo_actual = time(nullptr);
            double segundos_Transcurridos = difftime(tiempo_actual, track_Start_Time);

            if (!usuario_Ha_Cambiado_Pista && current_Track == -2 && segundos_Transcurridos >= 123.0) {
                random_Track();
            }
            else if (usuario_Ha_Cambiado_Pista && current_Track >= 0 && segundos_Transcurridos >= v_playlist_Musica[current_Track].duracion_Cancion - 0.5) {
                next_Track();
            }
        }
    }

    else if (en_juego)
    {
        if (reproducirAleatoria_Pendiente) {
            random_Track();
            reproducirAleatoria_Pendiente = false;
        }

        else if (!playing_Musica) {
            reproducirAleatoria_Pendiente = true;  // activa bandera para siguiente frame
        }
    }
}

void Gestor_Audio::next_Track()
{
    if (v_playlist_Musica.empty()) return;
    if (current_Track == -2) current_Track = 0;
    else current_Track = (current_Track + 1) % v_playlist_Musica.size();

    usuario_Ha_Cambiado_Pista = true;
    play_Music(v_playlist_Musica[current_Track].ruta_Cancion, false);
    track_Start_Time = time(nullptr);
    std::cout << "Siguiente pista: " << v_playlist_Musica[current_Track].nombre_Cancion << std::endl;
}

void Gestor_Audio::previous_Track()
{
    if (v_playlist_Musica.empty()) return;
    if (current_Track == -2) current_Track = 0;
    else if (current_Track == 0) current_Track = v_playlist_Musica.size() - 1;
    else current_Track--;

    usuario_Ha_Cambiado_Pista = true;
    play_Music(v_playlist_Musica[current_Track].ruta_Cancion, false);
    track_Start_Time = time(nullptr);
    std::cout << "Pista anterior: " << v_playlist_Musica[current_Track].nombre_Cancion << std::endl;
}

void Gestor_Audio::stop_Musica()
{
    ETSIDI::stopMusica();
    playing_Musica = false;
    std::cout << "Musica detenida." << std::endl;
}

void Gestor_Audio::pause_Musica()
{
    if (!playing_Musica) return;

    if (paused_Track)
    {
        play_Music(v_playlist_Musica[current_Track].ruta_Cancion, false);
        track_Start_Time = time(nullptr);
        paused_Track = false;
        std::cout << "Resumiendo musica." << std::endl;
    }

    else
    {
        ETSIDI::stopMusica();
        paused_Track = true;
        std::cout << "Música pausada." << std::endl;
    }
}

void Gestor_Audio::play_Title_Screen_Music()
{
    ETSIDI::stopMusica();
    ETSIDI::playMusica("sonidos/Banda_Sonora/soundtrack_Title_Screen.wav", false);
    track_Start_Time = time(nullptr);
    playing_Musica = true;
    paused_Track = false;
    current_Track = -2;
    usuario_Ha_Cambiado_Pista = false;
    std::cout << "Música de título iniciada." << std::endl;
}

int Gestor_Audio::get_current_Track()
{
    return current_Track;
}

std::string Gestor_Audio::get_current_Track_Name()
{
    if (current_Track == -2)
        return "TitleScreen";
    if (current_Track >= 0 && current_Track < static_cast<int>(v_playlist_Musica.size()))
        return v_playlist_Musica[current_Track].nombre_Cancion;
    return "Ninguna";
}
