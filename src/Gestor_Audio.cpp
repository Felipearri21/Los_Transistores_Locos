// INCLUSIÓN DE LIBRERÍAS Y FICHEROS DE CABECERA
#include "Gestor_Audio.h"

// DEFINICIÓN DE VARIABLES ESTÁTICAS
std::vector<std::string> Gestor_Audio::v_playlist_Musica; // Vector de pistas de audio
int Gestor_Audio::current_Track = -1;                      // Número de la pista de audio actual
bool Gestor_Audio::playing_Musica = false;                 // Indica si la música se está reproduciendo
time_t Gestor_Audio::track_Start_Time = time(nullptr);     // Tiempo de inicio de la pista actual

// MÉTODOS DE LA CLASE GESTOR AUDIO

void Gestor_Audio::set_Gestor_Audio() // Inicializa el Gestor de Audio
{
    // Inicializamos la semilla aleatoria.
    srand(static_cast<unsigned int>(time(NULL)));

    // Rellena la playlist con las canciones de la carpeta.
    // (En un entorno real podrías leer el directorio, pero aquí usamos un listado predefinido).
    v_playlist_Musica.push_back("sonidos/Banda_Sonora/soundtrack_Dama_y_Almohada.wav");
    v_playlist_Musica.push_back("sonidos/Banda_Sonora/soundtrack_Gambito_y_Furioso.wav");
    v_playlist_Musica.push_back("sonidos/Banda_Sonora/soundtrack_Jaque_Over.wav");
    v_playlist_Musica.push_back("sonidos/Banda_Sonora/soundtrack_Peon_Pisando_Fino.wav");
    v_playlist_Musica.push_back("sonidos/Banda_Sonora/soundtrack_Susurros_del_Enroque.wav");
    v_playlist_Musica.push_back("sonidos/Banda_Sonora/soundtrack_Todo_por_un_5.wav");
}

void Gestor_Audio::set_Volumen(int volumen)
{
    // Si ETSIDI dispone de una función para ajustar el volumen, se invoca aquí.
    // Por ejemplo: ETSIDI::setVolume(volumen);
    // En este ejemplo, solo se muestra un mensaje.
    std::cout << "Volumen cambiado a: " << volumen << std::endl;
}

void Gestor_Audio::play_Music(const std::string& track, bool repeat)
{
    // Reproduce la pista usando ETSIDI y actualiza el flag.
    ETSIDI::playMusica(track.c_str(), repeat);
    playing_Musica = true;
}

void Gestor_Audio::random_Track()
{
    if (v_playlist_Musica.empty()) return;
    int nuevoIndice = current_Track;
    // Selecciona un índice aleatorio distinto del actual
    while (nuevoIndice == current_Track) {
        nuevoIndice = rand() % static_cast<int>(v_playlist_Musica.size());
    }
    current_Track = nuevoIndice;
}

void Gestor_Audio::update_Musica(Estado_Menu estado)
{
    // Determinamos si se debe reproducir música en función del estado.
    bool reproduce_Musica =
        (estado == Estado_Menu::TITLE_SCREEN ||
            estado == Estado_Menu::MAIN_MENU ||
            estado == Estado_Menu::SETTINGS);

    if (reproduce_Musica)
    {
        if (!playing_Musica)
        {
            // Inicializa la música de la pantalla de título.
            play_Title_Screen_Music();
        }
        else
        {
            // Obtenemos el tiempo actual
            time_t tiempo_actual = time(nullptr);
            double segundos_Transcurridos = difftime(tiempo_actual, track_Start_Time);

            // Si han pasado 123 segundos (duración de la pista de título)
            if (segundos_Transcurridos >= 123.0)
            {
                // Cambia a una pista aleatoria de la playlist.
                random_Track();
                if (current_Track >= 0 && current_Track < static_cast<int>(v_playlist_Musica.size()))
                {
                    play_Music(v_playlist_Musica[current_Track], true);
                    track_Start_Time = time(nullptr); // Reinicia el contador para la nueva pista
                    std::cout << "Cambio a la pista: " << v_playlist_Musica[current_Track] << std::endl;
                }
            }
        }
    }
    else
    {
        // Si no estamos en estados que requieren música, detén el audio.
        if (playing_Musica)
        {
            stop_Musica();
            playing_Musica = false;
        }
    }
}

void Gestor_Audio::next_Track()
{
    // Fuerza el cambio a otra pista manualmente (por ejemplo, desde el botón de ajustes).
    if (v_playlist_Musica.empty())
    {
        return;
    }
    if (current_Track < 0) {
        random_Track();
        play_Music(v_playlist_Musica[current_Track], true);
        track_Start_Time = time(nullptr);
        std::cout << "Reproduciendo pista aleatoria: " << v_playlist_Musica[current_Track] << std::endl;
        return;
    }

    random_Track();

    if (current_Track >= 0 && current_Track < static_cast<int>(v_playlist_Musica.size()))
    {
        play_Music(v_playlist_Musica[current_Track], true);
        track_Start_Time = time(nullptr);
        std::cout << "Siguiente pista: " << v_playlist_Musica[current_Track] << std::endl;
    }
}

void Gestor_Audio::previous_Track()
{
    if (v_playlist_Musica.empty()) 
    {
		std::cout << "No hay pistas en la lista de reproduccion." << std::endl;
		return;
    }

    if (current_Track < 0) 
    {
        random_Track();
        play_Music(v_playlist_Musica[current_Track], true);
        track_Start_Time = time(nullptr);
        std::cout << "Reproduciendo pista aleatoria: " << v_playlist_Musica[current_Track] << std::endl;
        return;
    }

    int nuevo_Indice;
    if (current_Track <= 0) 
    {
        nuevo_Indice = static_cast<int>(v_playlist_Musica.size()) - 1;
    }
  
    else
    {
        nuevo_Indice = current_Track - 1;
    }
        
    current_Track = nuevo_Indice;
    play_Music(v_playlist_Musica[current_Track], true);
    track_Start_Time = time(nullptr);
    std::cout << "Pista anterior: " << v_playlist_Musica[current_Track] << std::endl;
}


void Gestor_Audio::stop_Musica()
{
    ETSIDI::stopMusica();
    playing_Musica = false;
    std::cout << "Musica detenida." << std::endl;
}

void Gestor_Audio::play_Title_Screen_Music()
{
    ETSIDI::playMusica("sonidos/Banda_Sonora/soundtrack_Title_Screen.wav", false);
    track_Start_Time = time(nullptr); // Registra el momento de inicio
    playing_Musica = true;
    std::cout << "Musica de titulo iniciada." << std::endl;
}





