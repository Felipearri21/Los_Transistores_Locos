// INCLUSION DE LIBRERIAS Y FICHEROS DE CABECERA //
#include "Gestor_Audio.h"

// DEFINICION DE VARIABLES ESTATICAS //

std::vector<Cancion> Gestor_Audio::v_playlist_Musica;
int Gestor_Audio::current_Track = -1;
bool Gestor_Audio::playing_Musica = false;
bool Gestor_Audio::paused_Track = false;
time_t Gestor_Audio::track_Start_Time = time(nullptr);

void Gestor_Audio::set_Gestor_Audio() 
{
    // Inicializamos la semilla aleatoria.
    srand(static_cast<unsigned int>(time(NULL)));

    // Vaciamos la lista por si se hubiese inicializado previamente.
    v_playlist_Musica.clear();

    // Cargamos la playlist con los objetos Cancion.
    v_playlist_Musica.push_back(
        Cancion
        (
            "Dama y Almohada",
            "sonidos/Banda_Sonora/soundtrack_Dama_y_Almohada.wav",
            143
        )
    );
    v_playlist_Musica.push_back
    (
        Cancion
        (
            "Gambito y Furioso",
            "sonidos/Banda_Sonora/soundtrack_Gambito_y_Furioso.wav",
            159
        )
    );
    v_playlist_Musica.push_back
    (
        Cancion
        (
            "Jaque Over",
            "sonidos/Banda_Sonora/soundtrack_Jaque_Over.wav",
            95
        )
    );
    v_playlist_Musica.push_back
    (
        Cancion
        (
            "Peon Pisando Fino",
            "sonidos/Banda_Sonora/soundtrack_Peon_Pisando_Fino.wav",
            160
        )
    );
    v_playlist_Musica.push_back
    (
        Cancion
        (
            "Susurros del Enroque",
            "sonidos/Banda_Sonora/soundtrack_Susurros_del_Enroque.wav",
            130
        )
    );
    v_playlist_Musica.push_back
    (
        Cancion
        (
            "Todo por un 5",
            "sonidos/Banda_Sonora/soundtrack_Todo_por_un_5.wav",
            129
        )
    );
}

void Gestor_Audio::set_Volumen(int volumen) 
{
    // Si ETSIDI dispone de una función para ajustar el volumen //
    std::cout << "Volumen cambiado a: " << volumen << std::endl;
}

void Gestor_Audio::play_Music(const std::string& track, bool repeat) 
{
    ETSIDI::playMusica(track.c_str(), repeat);
    playing_Musica = true;
}

void Gestor_Audio::random_Track() 
{
    if (v_playlist_Musica.empty())
    {
        return;
    }
     
    int nuevo_Indice = current_Track;
    while (nuevo_Indice == current_Track) {
        nuevo_Indice = rand() % static_cast<int>(v_playlist_Musica.size());
    }
    current_Track = nuevo_Indice;
}

void Gestor_Audio::update_Musica(Estado_Menu estado)
{
    // Determinamos si se debe reproducir la música en función del estado.
    bool reproduce_Musica =
        (
            estado == Estado_Menu::TITLE_SCREEN ||
            estado == Estado_Menu::MAIN_MENU ||
            estado == Estado_Menu::SETTINGS
         );

    if (reproduce_Musica) 
    {
        if (!playing_Musica) 
        {
            // Si aún no se ha iniciado, se reproduce la música de la pantalla de título.
            play_Title_Screen_Music();
        }
        else 
        {
            // Se obtiene el tiempo actual y se calcula el tiempo transcurrido.
            time_t tiempo_actual = time(nullptr);
            double segundos_Transcurridos = difftime(tiempo_actual, track_Start_Time);

            // Por ejemplo, si la pista de título dura 123 segundos, al finalizar (o superar ese tiempo)
            // se cambia a una pista aleatoria de la playlist.
            if (segundos_Transcurridos >= 123.0) {
                random_Track();
                if (current_Track >= 0 && current_Track < static_cast<int>(v_playlist_Musica.size())) {
                    play_Music(v_playlist_Musica[current_Track].ruta_Cancion, true);
                    track_Start_Time = time(nullptr); // Reinicia el contador para la nueva pista.
                    std::cout << "Cambio a la pista: " << v_playlist_Musica[current_Track].nombre_Cancion << std::endl;
                }
            }
        }
    }

    else 
    {
        // Si no se requiere música para el estado actual, se detiene la reproducción.
        if (playing_Musica) 
        {
            stop_Musica();
            playing_Musica = false;
        }
    }
}

void Gestor_Audio::next_Track() 
{
    if (v_playlist_Musica.empty())
    {
        return;
    }

    // Si current_Track es negativo (por ejemplo, se sigue reproduciendo la pista de título),
    // se asigna la primera pista (índice 0) // 
    if (current_Track < 0) 
    {
        current_Track = 0;
    }
     
    else
    {
        // Avanza al siguiente índice de manera secuencial, usando el operador módulo para envolver al inicio.
        current_Track = (current_Track + 1) % v_playlist_Musica.size();
    }

    // Reproduce la pista seleccionada // 
    play_Music(v_playlist_Musica[current_Track].ruta_Cancion, true);
    track_Start_Time = time(nullptr);
    std::cout << "Siguiente pista: " << v_playlist_Musica[current_Track].nombre_Cancion << std::endl;
}

void Gestor_Audio::previous_Track() 
{
    if (v_playlist_Musica.empty())
    {
        std::cout << "No hay pistas en la lista de reproduccion." << std::endl;
        return;
    }

    // Si aún no se ha seleccionado una pista (current_Track < 0), se asigna la primera.
    if (current_Track < 0) 
    {
        current_Track = 0;
    }

    else 
    {
        // Si estamos en la primera pista, volvemos a la última; de lo contrario, retrocedemos una posición.
        if (current_Track == 0)
        {
            current_Track = v_playlist_Musica.size() - 1;
        }
       
        else
            current_Track = current_Track - 1;
    }

    // Reproduce la pista seleccionada.
    play_Music(v_playlist_Musica[current_Track].ruta_Cancion, true);
    track_Start_Time = time(nullptr);
    std::cout << "Pista anterior: " << v_playlist_Musica[current_Track].nombre_Cancion << std::endl;
}

void Gestor_Audio::stop_Musica() {
    ETSIDI::stopMusica();
    playing_Musica = false;
    std::cout << "Musica detenida." << std::endl;
}

void Gestor_Audio::pause_Musica()
{
    // Si no hay música, no hace nada.
    if (!playing_Musica)
    {
        return;
    }

    if (paused_Track) 
    {
        // Reanudar la música: Se reproduce el track actual (se reinicia desde el inicio).
        play_Music(v_playlist_Musica[current_Track].ruta_Cancion, true);
        track_Start_Time = time(nullptr);
        paused_Track = false;
        std::cout << "Resumiendo musica: " << v_playlist_Musica[current_Track].nombre_Cancion << std::endl;
    }

    else 
    {
        // Pausar la música.
        ETSIDI::stopMusica();
        paused_Track = true;
        std::cout << "Música pausada." << std::endl;
    }
}

void Gestor_Audio::play_Title_Screen_Music() 
{
    ETSIDI::playMusica("sonidos/Banda_Sonora/soundtrack_Title_Screen.wav", false);
    track_Start_Time = time(nullptr);
    playing_Musica = true;
    paused_Track = false; // Aseguramos que no está en pausa.
    current_Track = -2;  // Valor especial que indica que se está reproduciendo la música del título.
    std::cout << "Música de título iniciada." << std::endl;
}

int Gestor_Audio::get_current_Track() 
{
    return current_Track;
}

std::string Gestor_Audio::get_current_Track_Name() 
{
    if (current_Track == -2) 
    {
        return "Title Screen Track";
    }
    if (current_Track >= 0 && current_Track < static_cast<int>(v_playlist_Musica.size())) 
    {
        return v_playlist_Musica[current_Track].nombre_Cancion;
    }

    return "Ninguna";
}