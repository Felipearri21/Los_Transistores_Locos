#pragma once

// INCLUSI�N DE LIBRER�AS Y FICHEROS DE CABECERA //

// Inclusion de Librer�as Estandar //
#include <string>

// Inclusion de Librer�a de OpenGL //
#include "freeglut.h"

// Inclusion de Ficheros de Cabecera Locales //
#include "Color.h"

// DEFINICI�N DE CLASES Y ESTRUCTURAS //

// Clase que representa un Bot�n del Men� //

class Boton
{	
public:

	// M�TODOS PRINCIPALES DE LA CLASE MENU //

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

	void draw_Boton(); // Muestra el Bot�n //

	bool contact_Boton(int mouse_X, int mouse_Y)const; // Comprueba si el Rat�n est� en el Boton //
		
private:

	// PAR�METROS PRIVADOS DE LA CLASE BOTON //

	friend class Menu; // Permite que la clase Menu acceda a los miembros privados de Boton.

	// Identificador del Bot�n //

	int ID_Boton;

	// Texto del Bot�n //
	std::string Texto_Boton;

	// Color del Bot�n //
	Color Color_Boton;

	// Coordenadas Esquina Inferior Izquierda //
	int X_Boton;
	int Y_Boton;

	// Dimensiones del Bot�n //
	int Ancho_Boton;
	int Altura_Boton;
};

