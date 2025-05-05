#pragma once

// INCLUSIÓN DE LIBRERÍAS Y FICHEROS DE CABECERA //

// Inclusion de Ficheros de Cabecera Locales //
#include "Funciones_Globales.h"

// FUNCIONES GLOBALES DE ESCRITURA Y GESTION DE TEXTO //

// Función auxiliar para dibujar texto usando una fuente bitmap //

void draw_BitmapText(const std::string& text, float x, float y)
{
    glRasterPos2f(x, y);

    for (char c : text)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

// Función auxiliar para calcular el ancho del texto usando una fuente bitmap //

int calculate_Ancho_Texto(const std::string& texto, void* fuente)
{
    int ancho_Total = 0;
    for (char c : texto)
    {
        ancho_Total += glutBitmapWidth(fuente, c);
    }
    return ancho_Total;
}