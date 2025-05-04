#pragma once

// INCLUSIÓN DE LIBRERÍAS Y FICHEROS DE CABECERA //

// Inclusion de Librerías Estandar //
#include <string>

// Inclusion de Librería de OpenGL //
#include "freeglut.h"

// Inclusion de Ficheros de Cabecera Locales //
#include "Color.h"

// DEFINICIÓN DE CLASES Y ESTRUCTURAS //

// Clase que representa un Botón del Menú //

class Boton
{	
public:

	// MÉTODOS PRINCIPALES DE LA CLASE MENU //

	Boton // Constructor por Defecto // 
	(
		int id,
		std::string texto,
		Color color, 
		int x, 
		int y, 
		int ancho = 400, 
		int altura = 50
	); 

	void draw_Boton(); // Muestra el Botón //

	bool contact_Boton(int mouse_X, int mouse_Y)const; // Comprueba si el Ratón está en el Boton //
		
private:

	// PARÁMETROS PRIVADOS DE LA CLASE BOTON //

	friend class Menu; // Permite que la clase Menu acceda a los miembros privados de Boton.

	// Identificador del Botón //

	int ID_Boton;

	// Texto del Botón //
	std::string Texto_Boton;

	// Color del Botón //
	Color Color_Boton;

	// Coordenadas Esquina Inferior Izquierda //
	int X_Boton;
	int Y_Boton;

	// Dimensiones del Botón //
	int Ancho_Boton;
	int Altura_Boton;
};

