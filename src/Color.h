#pragma once

// INCLUSI�N DE LIBRER�AS Y FICHEROS DE CABECERA //

// Inclusion de Librer�as Estandar //

// Inclusion de Librer�a de OpenGL //

// Inclusion de Ficheros de Cabecera Locales //

// DEFINICI�N DE CLASES Y ESTRUCTURAS //

class Color
{

public:

	// PAR�METROS DEL COLOR //

	unsigned char Rojo_Color{};
	unsigned char Verde_Color{};
	unsigned char Azul_Color{};

	// M�TODOS DE LA CLASE COLOR //

	void set_Color(unsigned char rojo, unsigned char verde, unsigned char azul); // Establece el color. //

	void implement_Color(); // Implementa el color. //
};

