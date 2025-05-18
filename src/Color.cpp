// INCLUSION DE FICHEROS Y LIBRERIAS //

// Libreria de OpenGL //

#include <freeglut.h>

// Ficheros Locales //

#include "Color.h"

// METODOS DE LA CLASE //

// Cosntructor //
Color::Color() : R(255), G(255), B(255) {}

Color::Color(unsigned char r, unsigned char g, unsigned char b)
    : R(r), G(g), B(b) 
{
}

void Color::set_Color(unsigned char r, unsigned char g, unsigned char b) 
{
    R = r;
    G = g;
    B = b;
}

void Color::implement_Color() const 
{
    glColor3ub(R, G, B);
}
