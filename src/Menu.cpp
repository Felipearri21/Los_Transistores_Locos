// INCLUSION DE LIBRERIAS Y FICHEROS DE CABECERA //

// Inclusion de Librerias Estandar //
#include <iostream>

// Inclusion de Libreria de OpenGL //
#include "freeglut.h"

// Inclusion de Libreria de ETSIDI //
#include "ETSIDI.h"

// Inclusion de Ficheros de Encabezado Locales //
#include "Menu.h"

// CONSTRUCTORES //

Menu::Menu()
{
    set_Menu();
    set_Estado_Menu(Estado_Menu::TITLE_SCREEN);
}

// METODOS DE LA CLASE MENU //

void Menu::set_Menu()
{
    // Aqui se pueden agregar inicializaciones adicionales si es necesario //
}

void Menu::set_Estado_Menu(Estado_Menu estado)
{
    Estado_Actual_Menu = estado;
}

void Menu::draw_Menu() // Muestra el Menu //
{
    // Configuramos una proyeccion ortografica segun el sistema logico actual (800 x 600) //
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    if (Estado_Actual_Menu == Estado_Menu::TITLE_SCREEN)
    {
        // Dibujar el fondo del menu principal con una textura //
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/menu_principal.png").id);
        glDisable(GL_LIGHTING);
        glBegin(GL_POLYGON);
        glColor3f(1, 1, 1); // Se garantiza que la textura se muestre sin modificaciones de color //
        // Asignamos las coordenadas de textura y los v�rtices del quad (usamos el sistema de 800x600) //
        glTexCoord2d(0, 1); glVertex2i(0, 0);
        glTexCoord2d(1, 1); glVertex2i(800, 0);
        glTexCoord2d(1, 0); glVertex2i(800, 600);
        glTexCoord2d(0, 0); glVertex2i(0, 600);
        glEnd();
        glEnable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);

        glColor3f(1, 1, 1);
        draw_BitmapText("Presiona cualquier tecla para comenzar", 220, 150);
    }
    else if (Estado_Actual_Menu == Estado_Menu::MAIN_MENU)
    {
        // Dibujar el fondo del menu principal con una textura //
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/menu_principal.png").id);
        glDisable(GL_LIGHTING);
        glBegin(GL_POLYGON);
        glColor3f(1, 1, 1); // Se garantiza que la textura se muestre sin modificaciones de color //
        // Asignamos las coordenadas de textura y los vertices del quad (usamos el sistema de 800x600) //
        glTexCoord2d(0, 1); glVertex2i(0, 0);
        glTexCoord2d(1, 1); glVertex2i(800, 0);
        glTexCoord2d(1, 0); glVertex2i(800, 600);
        glTexCoord2d(0, 0); glVertex2i(0, 600);
        glEnd();
        glEnable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);

        for (auto& btn : v_Botones_Main_Menu)
        {
            btn.draw_Boton();
        }
    }

    else if (Estado_Actual_Menu == Estado_Menu::SETTINGS)
    {
        glColor3f(0.8f, 0.8f, 1.0f);
        glBegin(GL_QUADS);
        glVertex2i(0, 0);
        glVertex2i(800, 0);
        glVertex2i(800, 600);
        glVertex2i(0, 600);
        glEnd();

        for (auto& btn : v_Botones_Settings)
        {
            btn.draw_Boton();
        }
    }
    // Se pueden introducir otros estados (AJEDREZ, ALAMOS, SILVERMAN, GAME_OVER) segun se requiera //

    glPopAttrib();
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void Menu::keyboard_Menu(unsigned char key)
{
    if (Estado_Actual_Menu == Estado_Menu::TITLE_SCREEN)
    {
        Estado_Actual_Menu = Estado_Menu::MAIN_MENU; // Cambia al men� principal al presionar cualquier tecla //
    }

    if (key == 27) // Tecla ESC //
    {
        if (Estado_Actual_Menu != Estado_Menu::SETTINGS)
        {
            Estado_Actual_Menu = Estado_Menu::SETTINGS; // Abre el menu de ajustes //
        }
        else if (Estado_Actual_Menu == Estado_Menu::SETTINGS)
        {
            Estado_Actual_Menu = Estado_Menu::MAIN_MENU; // Regresa al menu principal //
        }
    }
}

void Menu::mouse_Menu(int mouse_X, int mouse_Y)
{
    // Cuando se esta en la pantalla de titulo, se cambia directamente al menu principal //
    if (Estado_Actual_Menu == Estado_Menu::TITLE_SCREEN)
    {
        Estado_Actual_Menu = Estado_Menu::MAIN_MENU;
    }

    if (Estado_Actual_Menu == Estado_Menu::MAIN_MENU)
    {
        for (const auto& btn : v_Botones_Main_Menu)
        {
            if (btn.contact_Boton(mouse_X, mouse_Y))
            {
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
                default:
                    std::cout << "Opcion no valida" << std::endl;
                    exit(0);
                    break;
                }
                return;
            }
        }
    }

    if (Estado_Actual_Menu == Estado_Menu::SETTINGS)
    {
        for (const auto& btn : v_Botones_Settings)
        {
            if (btn.contact_Boton(mouse_X, mouse_Y))
            {
                switch (btn.ID_Boton)
                {
                case 21:
                    std::cout << "Subir Volumen seleccionado" << std::endl;
                    // Introducir la logica para subir el volumen //
                    break;
                case 22:
                    std::cout << "Bajar Volumen seleccionado" << std::endl;
                    // Introducir la logica para bajar el volumen //
                    break;
                case 23:
                    std::cout << "Menu Principal seleccionado" << std::endl;
                    Estado_Actual_Menu = Estado_Menu::MAIN_MENU;
                    break;
                case 24:
                    std::cout << "Salir seleccionado" << std::endl;
                    Estado_Actual_Menu = Estado_Menu::EXIT;
                    exit(0);
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

    if (Estado_Actual_Menu == Estado_Menu::AJEDREZ)
    {
        // Aqui se puede agregar el manejo del raton para el estado AJEDREZ si es necesario //
    }

    if (Estado_Actual_Menu == Estado_Menu::ALAMOS)
    {
        // Aqui se puede agregar el manejo del raton para el estado ALAMOS si es necesario //
    }

    if (Estado_Actual_Menu == Estado_Menu::SILVERMAN)
    {
        // Aqui se puede agregar el manejo del raton para el estado SILVEMAN si es necesario //
    }

    if (Estado_Actual_Menu == Estado_Menu::GAME_OVER)
    {
        // Aqui se puede agregar el manejo del raton para el estado GAME_OVER si es necesario //
    }
}