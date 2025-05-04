// INCLUSI�N DE LIBRER�AS Y FICHEROS DE CABECERA //

// Inclusion de Librer�as Estandar //
#include <iostream>

// Inclusion de Fichero de Encabezado Locales //
#include "Menu.h"

// CONSTRUCTORES //

Menu::Menu()
{
	// Inicializa el men� en el estado principal.

	set_Menu();
	set_Estado_Menu(Estado_Menu::MAIN_MENU);
}

// METODOS DE LA CLASE MENU //

// Inicializa el Men� //

void Menu::set_Menu()
{
    // Botones del Men� Principal //
    v_Botones_Main_Menu.push_back({ 200, 400, 400, 50, "Ajedrez Normal" });
    v_Botones_Main_Menu.push_back({ 200, 330, 400, 50, "Los Alamos" });
    v_Botones_Main_Menu.push_back({ 200, 260, 400, 50, "Silverman 4x4" });
    v_Botones_Main_Menu.push_back({ 200, 190, 400, 50, "Ajustes" });
    // Mensaje de depuraci�n para confirmar carga de botones.
    std::cout << "Botones del Main Menu: " << v_Botones_Main_Menu.size() << std::endl;

    // Botones del Men� de Ajustes //
    v_Botones_Settings.push_back({ 200, 400, 400, 50, "Subir Volumen" });
	v_Botones_Settings.push_back({ 200, 330, 400, 50, "Bajar Volumen" });
    v_Botones_Settings.push_back({ 200, 260, 400, 50, "Menu Principal" });
    v_Botones_Settings.push_back({ 200, 190, 400, 50, "Salir" });

	// Botones de la Pantalla de Ajedrez //
    
	// Botones de la Pantalla de Los �lamos //

	// Botones de la Pantalla de Silverman 4x4 //

	// Botones de la Pantalla de Game Over //

}

// Cambia el Estado del Men� //

void Menu::set_Estado_Menu (Estado_Menu estado) 
{
    Estado_Actual_Menu = estado;
}

// Muestra el Men� //

void Menu::draw_Menu() 
{
    // Como main.cpp configura la proyecci�n en perspectiva, cambiamos temporalmente a una proyecci�n ortogr�fica.
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    // Suponemos un sistema de coordenadas 2D de 800x600.
    gluOrtho2D(0, 800, 0, 600);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Desactivamos la iluminaci�n para dibujar el men� en 2D.
    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    if (Estado_Actual_Menu == Estado_Menu::MAIN_MENU) 
    {
        // Dibujar fondo para men� principal.
        glColor3f(0.9f, 0.9f, 0.9f);
        glBegin(GL_QUADS);
        glVertex2i(0, 0);
        glVertex2i(800, 0);
        glVertex2i(800, 600);
        glVertex2i(0, 600);
        glEnd();

        // Dibujar cada bot�n del men� principal.
        for (const auto& btn : v_Botones_Main_Menu) 
        {
            // Fondo del bot�n.
            glColor3f(0.6f, 0.6f, 0.6f);
            glBegin(GL_QUADS);
            glVertex2i(btn.X_Boton, btn.Y_Boton);
            glVertex2i(btn.X_Boton + btn.Ancho_Boton, btn.Y_Boton);
            glVertex2i(btn.X_Boton + btn.Ancho_Boton, btn.Y_Boton + btn.Altura_Boton);
            glVertex2i(btn.X_Boton, btn.Y_Boton + btn.Altura_Boton);
            glEnd();

            // Texto del bot�n (en negro).
            glColor3f(0, 0, 0);
            float textX = btn.X_Boton + 20;  // Offset para centrar (puedes ajustar).
            float textY = btn.Y_Boton + btn.Altura_Boton / 2;
            draw_BitmapText(btn.Texto_Boton, textX, textY);
        }
    }

    else if (Estado_Actual_Menu == Estado_Menu::SETTINGS) 
    {
        // Dibujar fondo para la pantalla de ajustes.
        glColor3f(0.8f, 0.8f, 1.0f);
        glBegin(GL_QUADS);
        glVertex2i(0, 0);
        glVertex2i(800, 0);
        glVertex2i(800, 600);
        glVertex2i(0, 600);
        glEnd();

        // Dibujar los botones de la pantalla de ajustes.
        for (const auto& btn : v_Botones_Settings) 
        {
            glColor3f(0.6f, 0.6f, 0.6f);
            glBegin(GL_QUADS);
            glVertex2i(btn.X_Boton, btn.Y_Boton);
            glVertex2i(btn.X_Boton + btn.Ancho_Boton, btn.Y_Boton);
            glVertex2i(btn.X_Boton + btn.Ancho_Boton, btn.Y_Boton + btn.Altura_Boton);
            glVertex2i(btn.X_Boton, btn.Y_Boton + btn.Altura_Boton);
            glEnd();
            glColor3f(0, 0, 0);
            float textX = btn.X_Boton + 20;
            float textY = btn.Y_Boton + btn.Altura_Boton / 2;
            draw_BitmapText(btn.Texto_Boton, textX, textY);
        }
    }

    else if (Estado_Actual_Menu == Estado_Menu::AJEDREZ)
    {
		// Incluir l�gica de dibujo para el juego de ajedrez //
    }

	else if (Estado_Actual_Menu == Estado_Menu::ALAMOS)
	{
		// Incluir l�gica de dibujo para el juego de ajedrez //
	}

	else if (Estado_Actual_Menu == Estado_Menu::SILVERMAN)
	{
		// Incluir l�gica de dibujo para el juego de ajedrez //
	}

	else if (Estado_Actual_Menu == Estado_Menu::GAME_OVER)
	{
		// Incluir l�gica de dibujo para la pantalla de Game Over //
	}

    else if (Estado_Actual_Menu == Estado_Menu::EXIT)
    {
        // Incluir l�gica de salida del juego // 
    }

    glPopAttrib();
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);  // Vuelve al modo habitual.
}

// Movimiento del Rat�n en el Men� //

void Menu::mouse_Menu(int mouse_X, int mouse_Y) 
{
    if (Estado_Actual_Menu == Estado_Menu::MAIN_MENU) 
    {
        for (const auto& btn : v_Botones_Main_Menu) 
        {
            if (
                mouse_X >= btn.X_Boton && mouse_X <= btn.X_Boton + btn.Ancho_Boton &&
                mouse_Y >= btn.Y_Boton && mouse_Y <= btn.Y_Boton + btn.Altura_Boton) 
            {
                if (btn.Texto_Boton == "Ajedrez Normal") 
                {
                    std::cout << "Ajedrez Normal seleccionado" << std::endl;
                    Estado_Actual_Menu = Estado_Menu::AJEDREZ;  // Aqu� iniciar�as el juego en modo Normal.
                }

                else if (btn.Texto_Boton == "Los Alamos") 
                {
                    std::cout << "Los �lamos seleccionado" << std::endl;
                    Estado_Actual_Menu = Estado_Menu::ALAMOS;  // Inicia el juego en modo Los �lamos.
                }

                else if (btn.Texto_Boton == "Silverman 4x4") 
                {
                    std::cout << "Silverman 4x4 seleccionado" << std::endl;
                    Estado_Actual_Menu = Estado_Menu::SILVERMAN;  // Inicia el juego en modo Silverman 4x4.
                }

                else if (btn.Texto_Boton == "Ajustes") 
                {
                    Estado_Actual_Menu = Estado_Menu::SETTINGS; // Cambia al men� de ajustes.
                }

                return;
            }
        }
    }

    else if (Estado_Actual_Menu == Estado_Menu::SETTINGS) 
    {
        for (const auto& btn : v_Botones_Settings) 
        {
            if (
                mouse_X >= btn.X_Boton && mouse_X <= btn.X_Boton + btn.Ancho_Boton &&
                mouse_Y >= btn.Y_Boton && mouse_Y <= btn.Y_Boton + btn.Altura_Boton) 
            {
                if (btn.Texto_Boton == "Subir Volumen") 
                {
                    std::cout << "Subiendo volumen..." << std::endl;
                    // Aqu� llamar�as a la funci�n correspondiente del m�dulo de audio.
                }

                if (btn.Texto_Boton == "Bajar Volumen")
                {
                    std::cout << "Bajando volumen..." << std::endl;
                    // Aqu� llamar�as a la funci�n correspondiente del m�dulo de audio.
                }

                else if (btn.Texto_Boton == "Menu Principal") 
                {
                    Estado_Actual_Menu = Estado_Menu::MAIN_MENU;
                }

                else if (btn.Texto_Boton == "Salir") 
                {
                    std::cout << "Saliendo de la aplicaci�n..." << std::endl;
                    exit(0);
                }

                return;
            }
        }
    }

    else if (Estado_Actual_Menu == Estado_Menu::AJEDREZ)
    {
		// Incluir l�gica del rat�n para el juego de ajedrez.
    }

    else if (Estado_Actual_Menu == Estado_Menu::ALAMOS)
    {
        // Incluir l�gica del rat�n para el juego de ajedrez.
    }

    else if (Estado_Actual_Menu == Estado_Menu::SILVERMAN)
    {
        // Incluir l�gica del rat�n para el juego de ajedrez.
    }
}

// DESTRUCTOR //

Menu::~Menu() {}
