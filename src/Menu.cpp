// INCLUSIÓN DE LIBRERÍAS Y FICHEROS DE CABECERA

// Inclusión de Librerías Estándar
#include <iostream>

// Inclusión de Librería de OpenGL
#include "freeglut.h"

// Inclusión de Librería de ETSIDI
#include "ETSIDI.h"

// Inclusión de Ficheros de Encabezado Locales
#include "Menu.h"
#include "Funciones_Globales.h"
#include "Variables_Globales.h"
#include "Gestor_Audio.h"

// CONSTRUCTORES

Menu::Menu()
{
    set_Menu();
    set_Estado_Menu(Estado_Menu::TITLE_SCREEN);
}

// MÉTODOS DE LA CLASE MENU

void Menu::set_Menu()
{
    // Aquí se pueden agregar inicializaciones adicionales si es necesario.
}

void Menu::set_Estado_Menu(Estado_Menu estado)
{
    Estado_Actual_Menu = estado;
}

void Menu::draw_Menu() // Muestra el Menú
{
    // Se asume que la proyección ya está configurada a la resolución virtual en OnReshape().
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    switch (Estado_Actual_Menu)
    {
    case Estado_Menu::TITLE_SCREEN:
    {
        // Dibujar el fondo con textura (pantalla de título).
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/menu_principal_(1920x1080).png").id);
        glDisable(GL_LIGHTING);
        glBegin(GL_POLYGON);
        glColor3f(1, 1, 1); // Sin modificaciones de color.
        glTexCoord2d(0, 1); glVertex2i(0, 0);
        glTexCoord2d(1, 1); glVertex2i((int)virtual_Width, 0);
        glTexCoord2d(1, 0); glVertex2i((int)virtual_Width, (int)virtual_Height);
        glTexCoord2d(0, 0); glVertex2i(0, (int)virtual_Height);
        glEnd();
        glEnable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);

        {
            std::string Texto_Titulo = "Presiona cualquier tecla para comenzar";
            draw_BitmapText(Texto_Titulo, (virtual_Width - calculate_Ancho_Texto(Texto_Titulo)) / 2, virtual_Height / 4);
        }
        break;
    }
    case Estado_Menu::MAIN_MENU:
    {
        // Dibujar el fondo del Menú Principal.
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/menu_principal_(1920x1080).png").id);
        glDisable(GL_LIGHTING);
        glBegin(GL_POLYGON);
        glColor3f(1, 1, 1);
        glTexCoord2d(0, 1); glVertex2i(0, 0);
        glTexCoord2d(1, 1); glVertex2i((int)virtual_Width, 0);
        glTexCoord2d(1, 0); glVertex2i((int)virtual_Width, (int)virtual_Height);
        glTexCoord2d(0, 0); glVertex2i(0, (int)virtual_Height);
        glEnd();
        glEnable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);

        // Actualiza el botón central de audio (ID 16) para que muestre el nombre de la pista actual.
        for (auto& btn : v_Botones_Main_Menu)
        {
            if (btn.ID_Boton == 16)
            {
                btn.Texto_Boton = Gestor_Audio::get_current_Track_Name();
            }
        }
        // Dibuja todos los botones del Menú Principal (incluyendo los de audio).
        for (auto& btn : v_Botones_Main_Menu)
        {
            btn.draw_Boton();
        }
        break;
    }
    case Estado_Menu::SETTINGS:
    {
        // Dibujar fondo del Menú de Ajustes.
        glColor3f(0.8f, 0.8f, 1.0f);
        glBegin(GL_QUADS);
        glVertex2i(0, 0);
        glVertex2i((int)virtual_Width, 0);
        glVertex2i((int)virtual_Width, (int)virtual_Height);
        glVertex2i(0, (int)virtual_Height);
        glEnd();
        for (auto& btn : v_Botones_Settings)
        {
            btn.draw_Boton();
        }
        break;
    }

    case Estado_Menu::AJEDREZ:
    {
        // Aquí se puede agregar la logica para el estado de Ajedrez.
        std::cout << "Estado de Ajedrez seleccionado." << std::endl;

        break;
    }

	case Estado_Menu::ALAMOS:
	{
		// Aquí se puede agregar la logica para el estado de Los Álamos.
		std::cout << "Estado de Los Alamos seleccionado." << std::endl;
		break;
	}

    case Estado_Menu::SILVERMAN:
    {
        // Aquí se puede agregar la lógica para el estado de Silverman 4x4.
        std::cout << "Estado de Silverman 4x4 seleccionado." << std::endl;
        break;
    }


    default:
    {
        std::cout << "Estado de menu no valido. Volviendo al menu principal." << std::endl;
        Estado_Actual_Menu = Estado_Menu::MAIN_MENU;
        break;
    }
    } // Fin del switch

    glPopAttrib();
    glPopMatrix();
}

void Menu::keyboard_Menu(unsigned char key)
{
    if (Estado_Actual_Menu == Estado_Menu::TITLE_SCREEN)
    {
        Estado_Actual_Menu = Estado_Menu::MAIN_MENU; // Cambia a MAIN_MENU al presionar cualquier tecla.
    }

    if (key == 27) // Tecla ESC
    {
        if (Estado_Actual_Menu != Estado_Menu::SETTINGS)
        {
            Estado_Actual_Menu = Estado_Menu::SETTINGS; // Abre el Menú de Ajustes.
        }
        else
        {
            Estado_Actual_Menu = Estado_Menu::MAIN_MENU; // Regresa al Menú Principal.
        }
    }
}

void Menu::mouse_Menu(int mouse_X, int mouse_Y)
{
    // Si estamos en la pantalla de título, cambia directamente al Menú Principal.
    if (Estado_Actual_Menu == Estado_Menu::TITLE_SCREEN)
    {
        Estado_Actual_Menu = Estado_Menu::MAIN_MENU;
    }

    if (Estado_Actual_Menu == Estado_Menu::MAIN_MENU)
    {
        // Recorre los botones del Menú Principal.
        for (const auto& btn : v_Botones_Main_Menu)
        {
            if (btn.contact_Boton(mouse_X, mouse_Y)) // Se ha pulsado sobre el botón.
            {
                btn.sound_Boton(mouse_X, mouse_Y); // Reproduce el sonido asociado al botón.
                switch (btn.ID_Boton)
                {
                case 11:
                    std::cout << "Ajedrez Normal seleccionado" << std::endl;
                    Estado_Actual_Menu = Estado_Menu::AJEDREZ;
                    break;
                case 12:
                    std::cout << "Los Alamos seleccionado" << std::endl;
                    Estado_Actual_Menu = Estado_Menu::ALAMOS;
                    break;
                case 13:
                    std::cout << "Silverman 4x4 seleccionado" << std::endl;
                    Estado_Actual_Menu = Estado_Menu::SILVERMAN;
                    break;
                case 14:
                    std::cout << "Ajustes seleccionado" << std::endl;
                    Estado_Actual_Menu = Estado_Menu::SETTINGS;
                    break;
                    // Botones de control de audio:
                case 15: 
                    Gestor_Audio::previous_Track();
                    break;
                case 16: 
                    Gestor_Audio::pause_Musica();
                    break;
                case 17: 
                    Gestor_Audio::next_Track();
                    break;
                default:
                    std::cout << "Opcion no valida" << std::endl;
                    exit(0);
                    break;
                }
                return;
            }
        }
    }
    else if (Estado_Actual_Menu == Estado_Menu::SETTINGS)
    {
        // Gestión de clics para los botones del Menú de Ajustes.
        for (const auto& btn : v_Botones_Settings)
        {
            if (btn.contact_Boton(mouse_X, mouse_Y))
            {
                btn.sound_Boton(mouse_X, mouse_Y);
                switch (btn.ID_Boton)
                {
                case 21:
                    std::cout << "Subir Volumen seleccionado" << std::endl;
                    // Lógica para subir el volumen.
                    break;
                case 22:
                    std::cout << "Bajar Volumen seleccionado" << std::endl;
                    // Lógica para bajar el volumen.
                    break;
                case 23:
                    std::cout << "Menú Principal seleccionado" << std::endl;
                    Estado_Actual_Menu = Estado_Menu::MAIN_MENU;
                    break;
                case 24:
                    std::cout << "Salir seleccionado" << std::endl;
                    Estado_Actual_Menu = Estado_Menu::EXIT;
                    exit(0);
                    break;
                default:
                    std::cout << "Opcion no válida" << std::endl;
                    exit(0);
                    break;
                }
                return;
            }
        }
    }

    // Se pueden agregar manejos para otros estados (AJEDREZ, ALAMOS, etc.) si es necesario.
}