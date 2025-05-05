// INCLUSIÓN DE LIBRERÍAS Y FICHEROS DE CABECERA //

// Inclusion de Librerías Estandar //
#include <iostream>

// Inclusion de Librería de OpenGL //
#include "freeglut.h"

// Inclusion de Librería de ETSIDI //
#include "ETSIDI.h"

// Inclusion de Ficheros de Encabezado Locales //
#include "Menu.h"
#include "Funciones_Globales.h"
#include "Variables_Globales.h"

// CONSTRUCTORES //

Menu::Menu()
{
    set_Menu();
    set_Estado_Menu(Estado_Menu::TITLE_SCREEN);
}

// METODOS DE LA CLASE MENU //

void Menu::set_Menu()
{
    // Aquí se pueden agregar inicializaciones adicionales si es necesario //
}

void Menu::set_Estado_Menu(Estado_Menu estado)
{
    Estado_Actual_Menu = estado;
}

void Menu::draw_Menu() // Muestra el Menú //
{
    // Se asume que la proyección ya está configurada a la resolución virtual en OnReshape().
    // Solo hacemos un push/pop de la matriz para conservar el estado.
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);


    if (Estado_Actual_Menu == Estado_Menu::TITLE_SCREEN)
    {
        // Dibujar el fondo del menú principal con una textura.
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/menu_principal_(1920x1080).png").id);
        glDisable(GL_LIGHTING);
        glBegin(GL_POLYGON);
        glColor3f(1, 1, 1); // Se garantiza que la textura se muestre sin modificaciones de color.
        // Asignamos las coordenadas de textura y los vértices del quad (usamos el sistema de 800x600)
        glTexCoord2d(0, 1); glVertex2i(0, 0);
        glTexCoord2d(1, 1); glVertex2i((int)virtual_Width, 0);
        glTexCoord2d(1, 0); glVertex2i((int)virtual_Width, (int)virtual_Height);
        glTexCoord2d(0, 0); glVertex2i(0, (int)virtual_Height);
        glEnd();
        glEnable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);

        glColor3f(1, 1, 1);

        std::string Texto_Titulo = "Presiona cualquier tecla para comenzar";
        draw_BitmapText(Texto_Titulo, (virtual_Width - calculate_Ancho_Texto(Texto_Titulo))/2, virtual_Height/4);
    }
    else if (Estado_Actual_Menu == Estado_Menu::MAIN_MENU)
    {
        // Dibujar el fondo del menú principal con una textura.
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/menu_principal_(1920x1080).png").id);
        glDisable(GL_LIGHTING);
        glBegin(GL_POLYGON);
        glColor3f(1, 1, 1); // Se garantiza que la textura se muestre sin modificaciones de color.
        // Asignamos las coordenadas de textura y los vértices del quad (usamos el sistema de 800x600)
        glTexCoord2d(0, 1); glVertex2i(0, 0);
        glTexCoord2d(1, 1); glVertex2i((int)virtual_Width, 0);
        glTexCoord2d(1, 0); glVertex2i((int)virtual_Width, (int)virtual_Height);
        glTexCoord2d(0, 0); glVertex2i(0, (int)virtual_Height);
        glEnd();
        glEnable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);

        for (auto& btn : v_Botones_Main_Menu) // Dibuja los botones del menu principal //
        {
            btn.draw_Boton();
        }
    }

    else if (Estado_Actual_Menu == Estado_Menu::SETTINGS)
    {
        glColor3f(0.8f, 0.8f, 1.0f);
        glBegin(GL_QUADS);
        glVertex2i(0, 0);
        glVertex2i((int)virtual_Width, 0);
        glVertex2i((int)virtual_Width, (int)virtual_Height);
        glVertex2i(0, (int)virtual_Height);
        glEnd();

		for (auto& btn : v_Botones_Settings) // Dibuja los botones del menu de ajustes //
        {
            btn.draw_Boton();
        }
    }
    // Se pueden añadir otros estados (AJEDREZ, ALAMOS, SILVERMAN, GAME_OVER) según se requiera.

    glPopAttrib();
    glPopMatrix();
}

void Menu::keyboard_Menu(unsigned char key)
{
    if (Estado_Actual_Menu == Estado_Menu::TITLE_SCREEN)
    {
		Estado_Actual_Menu = Estado_Menu::MAIN_MENU; // Cambia al menú principal al presionar cualquier tecla //
    }

    if (key == 27) // Tecla ESC //
    {
		if (Estado_Actual_Menu != Estado_Menu::SETTINGS)
		{
			Estado_Actual_Menu = Estado_Menu::SETTINGS; // Abre el menu de ajustes //
		}
		else if (Estado_Actual_Menu == Estado_Menu::SETTINGS)
		{
			Estado_Actual_Menu = Estado_Menu::MAIN_MENU; // Regresa al menú principal //
		}
    }
}

void Menu::mouse_Menu(int mouse_X, int mouse_Y)
{
    // Cuando se está en la pantalla de título, se cambia directamente al menú principal //
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
                    // Lógica para subir el volumen.
                    break;
                case 22:
                    std::cout << "Bajar Volumen seleccionado" << std::endl;
                    // Lógica para bajar el volumen.
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
		// Aquí se puede agregar el manejo del ratón para el estado AJEDREZ si es necesario //
	}

    if (Estado_Actual_Menu == Estado_Menu::ALAMOS)
    {
        // Aquí se puede agregar el manejo del ratón para el estado ALAMOS si es necesario //
    }
    
    if (Estado_Actual_Menu == Estado_Menu::SILVERMAN)
    {
        // Aquí se puede agregar el manejo del ratón para el estado SILVEMAN si es necesario //
    }

    if (Estado_Actual_Menu == Estado_Menu::GAME_OVER)
    {
        // Aquí se puede agregar el manejo del ratón para el estado GAME_OVER si es necesario //
    }
}