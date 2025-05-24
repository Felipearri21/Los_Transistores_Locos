#pragma once

// INCLUSION DE FICHEROS Y LIBRERIAS // 

// Librerias Estandar //

#include <string>
#include <vector>

// Ficheros Locales //
#include "Boton.h"

// DECLARACION DE ESTADOS DEL MENU //

enum class Estado_Menu 
{
    TITLE_SCREEN,
    MAIN_MENU,
    SETTINGS,
    CREDITOS,
    AJEDREZ,
    ALAMOS,
    SILVERMAN,
    EXIT
};

// DECLARACION DE CLASE MENU //

class Menu 
{
public:

    // Constructor //
    Menu();

    // Metodos de la Clase //

    void set_Menu(); 
    void set_Estado_Menu(Estado_Menu estado);
    void set_Fondo(const std::string& ruta);
    const std::string& get_Fondo() const;


    void draw_Menu();
    void draw_Fondo(const std::string& ruta);

    void keyboard_Menu(unsigned char key);
    void mouse_Menu(int mouse_X, int mouse_Y);

    void actualizar_Hover(int mouse_X, int mouse_Y);

    Estado_Menu get_Estado_Menu() const { return Estado_Actual_Menu; }

private:

    // Parametros Privados de la Clase // 

    Estado_Menu Estado_Actual_Menu;

    std::string Fondo_Actual_Menu;

    std::vector<Boton> v_Botones_Main_Menu;
    std::vector<Boton> v_Botones_Settings;

    void execute_Accion_Boton(int id);

};