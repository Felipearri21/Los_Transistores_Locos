#pragma once

#ifndef MENU_H
#define MENU_H

// INCLUSI�N DE LIBRER�AS Y FICHEROS DE CABECERA //

// Inclusion de Librer�as Estandar //
#include <string>
#include <vector>

// Inclusion de Librer�a de OpenGL //
#include "freeglut.h"

// Inclusion de Librer�a de ETSIDI //
#include "ETSIDI.h"

// DEFINICI�N DE CLASES Y ESTRUCTURAS //

// Clase que representa un Bot�n del Men� //

struct Boton
{
	// Coordenadas Esquina Inferior Izquierda //
	int X_Boton;
	int Y_Boton;

	// Dimensiones del Bot�n //
	int Ancho_Boton;
	int Altura_Boton;

	// Texto del Bot�n //
	std::string Texto_Boton;
};

// Clase que representa los posibles Estados del Men� //

enum class Estado_Menu
{
	MAIN_MENU, // Menu Principal
	AJEDREZ, // Estado en el que se ha Seleccionado el Modo de Juego Normal //
	ALAMOS, // Estado en el que se ha Seleccionado el Modo de Juego Los �lamos //
	SILVERMAN, // Estado en el que se ha Seleccionado el Modo de Juego Silverman 4x4 //
	GAME_OVER, // Estado en el que se ha terminado el Juego //
	EXIT, // Estado en el que se ha salido del Juego //
	SETTINGS // Estado en el que se han cambiado los Ajustes del Juego //
};

// Clase que representa el Men� //

class Menu
{
public:

	// M�TODOS PRINCIPALES DE LA CLASE MENU //

	Menu(); // Constructor por Defecto //

	void set_Menu(); // Inicializa el Men� //
	void set_Estado_Menu(Estado_Menu estado); // Cambia el Estado del Men� //

	void draw_Menu(); // Muestra el Men� //

	void mouse_Menu(int mouse_X, int mouse_Y); // Movimiento del Rat�n en el Men� //

	~Menu(); // Destructor //

	// M�TODOS AUXILIARES DE LA CLASE MENU //

	// Funci�n para obtener el estado actual del men� //

	Estado_Menu get_Estado_Menu() const { return Estado_Actual_Menu; } // Devuelve el Estado Actual del Men� //
	
	// Funci�n auxiliar para dibujar texto usando una fuente bitmap.

	static void draw_BitmapText(const std::string &text, float x, float y) 
	{
		glRasterPos2f(x, y);
		for (char c : text) 
		{
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
		}
	}

private:
	
	// PAR�METROS PRIVADOS DE LA CLASE MENU //

	// Botones del Men� Principal //
	std::vector<Boton> v_Botones_Main_Menu; // Vector de Botones del Men� Principal//

	// Botones del Men� de Ajustes //
	std::vector<Boton> v_Botones_Settings; // Vector de Botones del Men� de Ajustes //
	
	// Estado del Men� //
	Estado_Menu Estado_Actual_Menu; // Estado Actual del Men� //
};

#endif // MENU_H