// INCLUSI�N DE LIBRER�AS Y FICHEROS DE CABECERA

// Inclusi�n de Librer�as Est�ndar
#include <iostream>

// Inclusi�n de Librer�a de OpenGL
#include "freeglut.h"

// Inclusi�n de Librer�a de ETSIDI
#include "ETSIDI.h"

// Inclusi�n de Ficheros de Encabezado Locales
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

// M�TODOS DE LA CLASE MENU

void Menu::set_Menu()
{
    // Aqu� se pueden agregar inicializaciones adicionales si es necesario.
}

void Menu::set_Estado_Menu(Estado_Menu estado)
{
    Estado_Actual_Menu = estado;
}

void Menu::draw_Menu() // Muestra el Men�
{
    // Se asume que la proyecci�n ya est� configurada a la resoluci�n virtual en OnReshape().
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    if (Estado_Actual_Menu == Estado_Menu::TITLE_SCREEN)
    {
        // Dibujar el fondo con textura (pantalla de t�tulo).
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

        std::string Texto_Titulo = "Presiona cualquier tecla para comenzar";
        draw_BitmapText(Texto_Titulo, (virtual_Width - calculate_Ancho_Texto(Texto_Titulo)) / 2, virtual_Height / 4);
    }
    else if (Estado_Actual_Menu == Estado_Menu::MAIN_MENU)
    {
        // Dibujar el fondo del Men� Principal.
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

        // Actualiza el bot�n central de audio (ID 16) para que muestre el nombre de la pista actual.
        for (auto& btn : v_Botones_Main_Menu)
        {
            if (btn.ID_Boton == 16)
            {
                // Utilizamos el accesor que implementamos en Gestor_Audio.
                btn.Texto_Boton = Gestor_Audio::get_current_Track_Name();
            }

        }

        // Dibuja todos los botones del Men� Principal (incluyendo los de audio).
        for (auto& btn : v_Botones_Main_Menu)
        {
            btn.draw_Boton();
        }
    }
    else if (Estado_Actual_Menu == Estado_Menu::SETTINGS)
    {
        // Dibujar fondo del Men� de Ajustes.
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
    }
    // Se pueden a�adir otros estados (AJEDREZ, ALAMOS, etc.)

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
            Estado_Actual_Menu = Estado_Menu::SETTINGS; // Abre el Men� de Ajustes.
        }
        else
        {
            Estado_Actual_Menu = Estado_Menu::MAIN_MENU; // Regresa al Men� Principal.
        }
    }
}

void Menu::mouse_Menu(int mouse_X, int mouse_Y)
{
    // Si estamos en la pantalla de t�tulo, cambia directamente al Men� Principal.
    if (Estado_Actual_Menu == Estado_Menu::TITLE_SCREEN)
    {
        Estado_Actual_Menu = Estado_Menu::MAIN_MENU;
    }

    if (Estado_Actual_Menu == Estado_Menu::MAIN_MENU)
    {
        // Recorre los botones del Men� Principal.
        for (const auto& btn : v_Botones_Main_Menu)
        {
            if (btn.contact_Boton(mouse_X, mouse_Y)) // Se ha pulsado sobre el bot�n.
            {
                btn.sound_Boton(mouse_X, mouse_Y); // Reproduce el sonido asociado al bot�n.
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
                case 15: // Bot�n Audio Prev: Pista anterior.
                    Gestor_Audio::previous_Track();
                    break;
                case 16: // Bot�n Audio Current: No realiza acci�n.
                    // Se podr�a incluir retroalimentaci�n visual o sonora.
                    break;
                case 17: // Bot�n Audio Next: Pista siguiente.
                    Gestor_Audio::next_Track();
                    break;
                default:
                    std::cout << "Opci�n no v�lida" << std::endl;
                    exit(0);
                    break;
                }
                return;
            }
        }
    }
    else if (Estado_Actual_Menu == Estado_Menu::SETTINGS)
    {
        // Gesti�n de clics para los botones del Men� de Ajustes.
        for (const auto& btn : v_Botones_Settings)
        {
            if (btn.contact_Boton(mouse_X, mouse_Y))
            {
                btn.sound_Boton(mouse_X, mouse_Y);
                switch (btn.ID_Boton)
                {
                case 21:
                    std::cout << "Subir Volumen seleccionado" << std::endl;
                    // L�gica para subir el volumen.
                    break;
                case 22:
                    std::cout << "Bajar Volumen seleccionado" << std::endl;
                    // L�gica para bajar el volumen.
                    break;
                case 23:
                    std::cout << "Men� Principal seleccionado" << std::endl;
                    Estado_Actual_Menu = Estado_Menu::MAIN_MENU;
                    break;
                case 24:
                    std::cout << "Salir seleccionado" << std::endl;
                    Estado_Actual_Menu = Estado_Menu::EXIT;
                    exit(0);
                    break;
                default:
                    std::cout << "Opcion no v�lida" << std::endl;
                    exit(0);
                    break;
                }
                return;
            }
        }
    }

    // Se pueden agregar manejos para otros estados (AJEDREZ, ALAMOS, etc.) si es necesario.
}