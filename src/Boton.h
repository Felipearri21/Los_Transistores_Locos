#pragma once

// INCLUSION DE FICHEROS Y LIBRERIAS //

// Librerias Estandar //
#include <string>

// Librerias de OpenGL //

#include "freeglut.h"

// Ficheros Locales //

#include "Color.h"

// DECLARACION DE CLASE BOTON //

class Boton 
{
public:

    // Constructor //

    Boton(int id, std::string texto, Color color, int x, int y, int ancho = 400, int altura = 50);

    // Metodos de la Clase //

    void draw_Boton();

    bool contact_Boton(int mouse_X, int mouse_Y) const;

    void sound_Boton(int mouse_X, int mouse_Y) const;

    void set_ColorRGB(int r, int g, int b); //  Metodo para Cambiar el Color Externamente //

    bool hovered = false;

    int ID_Boton;

    std::string Texto_Boton;

private:
    Color Color_Boton;
    int X_Boton;
    int Y_Boton;
    int Ancho_Boton;
    int Altura_Boton;

    friend class Menu;
};
