#pragma once

// INCLUSIÓN DE LIBRERÍAS Y FICHEROS DE CABECERA //

// Inclusion de Librerías Estandar //
#include <string>

// Inclusion de Librería de OpenGL //
#include "freeglut.h"

// Inclusion de Ficheros de Cabecera Locales //

// FUNCIONES GLOBALES DE ESCRITURA Y GESTION DE TEXTO //

// Función auxiliar para dibujar texto usando una fuente bitmap //

void draw_BitmapText(const std::string &text, float x, float y);

// Función auxiliar para calcular el ancho del texto usando una fuente bitmap //

int calculate_Ancho_Texto(const std::string& texto, void *fuente = GLUT_BITMAP_HELVETICA_18);





