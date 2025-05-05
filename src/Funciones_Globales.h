#pragma once

// INCLUSI�N DE LIBRER�AS Y FICHEROS DE CABECERA //

// Inclusion de Librer�as Estandar //
#include <string>

// Inclusion de Librer�a de OpenGL //
#include "freeglut.h"

// Inclusion de Ficheros de Cabecera Locales //

// FUNCIONES GLOBALES DE ESCRITURA Y GESTION DE TEXTO //

// Funci�n auxiliar para dibujar texto usando una fuente bitmap //

void draw_BitmapText(const std::string &text, float x, float y);

// Funci�n auxiliar para calcular el ancho del texto usando una fuente bitmap //

int calculate_Ancho_Texto(const std::string& texto, void *fuente = GLUT_BITMAP_HELVETICA_18);





