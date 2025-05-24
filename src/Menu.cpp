// INCLUSION DE FICHEROS Y LIBRERIAS //

// // Librerias Estandar //

#include <algorithm>
#include <iostream>

// Libreria ETSIDI //

#include "ETSIDI.h"

// Ficheros Locales //

#include "Funciones_Globales.h"
#include "Gestor_Audio.h"
#include "Menu.h"
#include "Variables_Globales.h"


Menu::Menu() 
{
    set_Menu();
    set_Estado_Menu(Estado_Menu::TITLE_SCREEN);
}

void Menu::set_Menu() 
{
    Fondo_Actual_Menu = "imagenes/menu_principal_(1920x1080).png";

    v_Botones_Main_Menu = 
    {
        Boton(11, "Ajedrez Normal", Color(228,204,72), 195, 100, 250, 50),
        Boton(12, "Los Alamos", Color(228,204,72), 515, 100, 250, 50),
        Boton(13, "Silverman 4x4", Color(228,204,72), 835, 100, 250, 50),
        Boton(14, "Ajustes", Color(228,204,72), 1155, 100, 250, 50),
        Boton(16, "Ninguna", Color(228,204,72), 1445, 160, 310, 50),
        Boton(15, "<-", Color(228,204,72), 1445, 100, 150, 50),
        Boton(17, "->", Color(228,204,72), 1605, 100, 150, 50)
    };

    v_Botones_Settings = 
    {
        Boton(23, "Ver Creditos", Color(228,204,72), 760, 420),
        Boton(24, "Menu Principal", Color(228,204,72), 760, 340),
        Boton(25, "Salir", Color(228,204,72), 760, 260)
    };
}

void Menu::set_Estado_Menu(Estado_Menu estado) 
{
    Estado_Actual_Menu = estado;
}

void Menu::set_Fondo(const std::string& ruta) 
{
    Fondo_Actual_Menu = ruta;
}
const std::string& Menu::get_Fondo() const {
    return Fondo_Actual_Menu;
}

void Menu::draw_Menu() 
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    switch (Estado_Actual_Menu) 
    {
    case Estado_Menu::TITLE_SCREEN:

        draw_Fondo(Fondo_Actual_Menu);
        draw_BitmapText("Presiona cualquier tecla para comenzar",
            (virtual_Width - calculate_Ancho_Texto("Presiona cualquier tecla para comenzar")) / 2,
            virtual_Height / 4);

        break;

    case Estado_Menu::MAIN_MENU:
    {
        draw_Fondo(Fondo_Actual_Menu);

        for (auto& btn : v_Botones_Main_Menu)
        {
            if (btn.ID_Boton == 16)
            {
                btn.Texto_Boton = Gestor_Audio::get_current_Track_Name();
            }
        }

            for (auto& btn : v_Botones_Main_Menu)
            {

                btn.draw_Boton();
            }

            break;
    }

    case Estado_Menu::SETTINGS:
    {
        draw_Fondo("imagenes/menu_ajustes_(1920x1080).png");
        glColor3f(1.0f, 1.0f, 1.0f);
        draw_BitmapText("MENU DE AJUSTES", (virtual_Width - calculate_Ancho_Texto("MENU DE AJUSTES")) / 2, 600);

        for (auto& btn : v_Botones_Settings)
        {
            btn.draw_Boton();
        }

        break;
    }

    case Estado_Menu::CREDITOS:
    {
        draw_Fondo("imagenes/creditos_(1920x1080).png");
        

        std::vector<std::string> Creditos = 
        {
            "TRABAJO DE INFORMATICA. AJEDREZ EDITION",
            "",
            "Desarrollado por: LOS TRANSISTORES LOCOS",
            "",
            "Felipe Arriero Serrano",
            "Alvaro Carrasco Alvarez",
            "Jose Conejero Gonzalez",
            "Gonzalo Morcillo Garcia",
            "Cesar Zabala Martín",
            "",
            "Banda Sonora de: SUNO AI",
            "Framework ETSIDI + GLUT",
            "",
            "Version 1.0",
            "Curso 2024/2025",
            "",
            "Gracias por Jugar",
            "",
            "Pulsa ESC para volver"
        };

        int yBase = virtual_Height - 100;
        int espaciado = 40;

        for (size_t i = 0; i < Creditos.size(); ++i) 
        {
            int ancho = calculate_Ancho_Texto(Creditos[i]);
            int x = (virtual_Width - ancho) / 2;
            int y = yBase - static_cast<int>(i * espaciado);
            draw_BitmapText(Creditos[i], x, y);
        }
        break;
    }

    default:
    {


        break;
    }
    }

    glPopAttrib();
    glPopMatrix();
}

void Menu::keyboard_Menu(unsigned char key) 
{
    if (Estado_Actual_Menu == Estado_Menu::TITLE_SCREEN)
    {
        Estado_Actual_Menu = Estado_Menu::MAIN_MENU;
    }

    else if (key == 27)
    {
        Estado_Actual_Menu = (Estado_Actual_Menu == Estado_Menu::SETTINGS) ? Estado_Menu::MAIN_MENU : Estado_Menu::SETTINGS;
    }

    else if (Estado_Actual_Menu == Estado_Menu::CREDITOS && key == 27)
    {
        Estado_Actual_Menu = Estado_Menu::MAIN_MENU;
    }
        
}

void Menu::mouse_Menu(int mouse_X, int mouse_Y) 
{
    std::vector<Boton>* botones = nullptr;
    
    if (Estado_Actual_Menu == Estado_Menu::TITLE_SCREEN)
    {
        Estado_Actual_Menu = Estado_Menu::MAIN_MENU;
        return;
    }

    else if (Estado_Actual_Menu == Estado_Menu::MAIN_MENU)
    {
        botones = &v_Botones_Main_Menu;
    }

    else if (Estado_Actual_Menu == Estado_Menu::SETTINGS)
    {
        botones = &v_Botones_Settings;
    }

    else return;

    for (auto& btn : *botones) 
    {
        bool hover = btn.contact_Boton(mouse_X, mouse_Y);
        btn.hovered = hover;

        if (hover) 
        {
            btn.sound_Boton(mouse_X, mouse_Y);
            execute_Accion_Boton(btn.ID_Boton);
            return;
        }
    }
}

void Menu::actualizar_Hover(int mouse_X, int mouse_Y) 
{
    std::vector<Boton>* botones = nullptr;

    if (Estado_Actual_Menu == Estado_Menu::MAIN_MENU) 
    {
        botones = &v_Botones_Main_Menu;
    }
       
    else if (Estado_Actual_Menu == Estado_Menu::SETTINGS)
    {
        botones = &v_Botones_Settings;
    }
        
    else return;

    for (auto& btn : *botones) 
    {
        btn.hovered = btn.contact_Boton(mouse_X, mouse_Y);
    }
}

void Menu::execute_Accion_Boton(int id) 
{
    switch (id) 
    {
    case 11: Estado_Actual_Menu = Estado_Menu::AJEDREZ; break;
    case 12: Estado_Actual_Menu = Estado_Menu::ALAMOS; break;
    case 13: Estado_Actual_Menu = Estado_Menu::SILVERMAN; break;
    case 14: Estado_Actual_Menu = Estado_Menu::SETTINGS; break;
    case 15: Gestor_Audio::previous_Track(); break;
    case 16: Gestor_Audio::pause_Musica(); break;
    case 17: Gestor_Audio::next_Track(); break;
    case 23: Estado_Actual_Menu = Estado_Menu::CREDITOS; break;
    case 24: Estado_Actual_Menu = Estado_Menu::MAIN_MENU; break;
    case 25: Estado_Actual_Menu = Estado_Menu::EXIT; exit(0); break;
    default: break;
    }
}

void Menu::draw_Fondo(const std::string& ruta) 
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(ruta.c_str()).id);
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glTexCoord2d(0, 1); glVertex2i(0, 0);
    glTexCoord2d(1, 1); glVertex2i((int)virtual_Width, 0);
    glTexCoord2d(1, 0); glVertex2i((int)virtual_Width, (int)virtual_Height);
    glTexCoord2d(0, 0); glVertex2i(0, (int)virtual_Height);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

