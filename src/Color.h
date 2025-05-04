#pragma once

// INCLUSIÓN DE LIBRERÍAS Y FICHEROS DE CABECERA //

// Inclusion de Librerías Estandar //

// Inclusion de Librería de OpenGL //

// Inclusion de Ficheros de Cabecera Locales //

// DEFINICIÓN DE CLASES Y ESTRUCTURAS //

class Color
{

public:

	// PARÁMETROS DEL COLOR //

	unsigned char Rojo_Color{};
	unsigned char Verde_Color{};
	unsigned char Azul_Color{};

	// MÉTODOS DE LA CLASE COLOR //

	void set_Color(unsigned char rojo, unsigned char verde, unsigned char azul); // Establece el color. //

	void implement_Color(); // Implementa el color. //
};

