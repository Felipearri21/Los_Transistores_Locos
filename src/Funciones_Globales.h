#pragma once

// INCLUSION DE FICHEROS Y LIBRERIAS //

// Librerias Estandar //
#include <string>

// Librerias de OpenGL //
#include "freeglut.h"

// Ficheros Locales //

// FUNCIONES GLOBALES DE ESCRITURA Y GESTION DE TEXTO //

// Función auxiliar para dibujar texto usando una fuente bitmap //

void draw_BitmapText(const std::string &text, float x, float y);

// Función auxiliar para calcular el ancho del texto usando una fuente bitmap //

int calculate_Ancho_Texto(const std::string& texto, void *fuente = GLUT_BITMAP_HELVETICA_18);





