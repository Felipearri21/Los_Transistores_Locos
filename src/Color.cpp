// INCLUSIÓN DE LIBRERÍAS Y FICHEROS DE CABECERA //

// Inclusion de Librerías Estandar //

// Inclusion de Librería de OpenGL //
#include "freeglut.h"

// Inclusion de Ficheros de Cabecera Locales //
#include "Color.h"

// FUNCIONES DEL COLOR // 

void Color::set_Color(unsigned char rojo, unsigned char verde, unsigned char azul) // Establece el color. //
{
	Rojo_Color = rojo;
	Verde_Color = verde;
	Azul_Color = azul;
}

void Color::implement_Color() // Implementa el color. //
{
	glColor3ub (Rojo_Color, Verde_Color, Azul_Color);
}