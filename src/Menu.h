#pragma once

#ifndef MENU_H
#define MENU_H

// INCLUSIÓN DE LIBRERÍAS Y FICHEROS DE CABECERA //

// Inclusion de Librerías Estandar //
#include <string>
#include <vector>

// Inclusion de Librería de OpenGL //
#include "freeglut.h"

// Inclusion de Librería de ETSIDI //
#include "ETSIDI.h"

// DEFINICIÓN DE CLASES Y ESTRUCTURAS //

// Clase que representa un Botón del Menú //

struct Boton
{
	// Coordenadas Esquina Inferior Izquierda //
	int X_Boton;
	int Y_Boton;

	// Dimensiones del Botón //
	int Ancho_Boton;
	int Altura_Boton;

	// Texto del Botón //
	std::string Texto_Boton;
};

// Clase que representa los posibles Estados del Menú //

enum class Estado_Menu
{
	MAIN_MENU, // Menu Principal
	AJEDREZ, // Estado en el que se ha Seleccionado el Modo de Juego Normal //
	ALAMOS, // Estado en el que se ha Seleccionado el Modo de Juego Los Álamos //
	SILVERMAN, // Estado en el que se ha Seleccionado el Modo de Juego Silverman 4x4 //
	GAME_OVER, // Estado en el que se ha terminado el Juego //
	EXIT, // Estado en el que se ha salido del Juego //
	SETTINGS // Estado en el que se han cambiado los Ajustes del Juego //
};

// Clase que representa el Menú //

class Menu
{
public:

	// MÉTODOS PRINCIPALES DE LA CLASE MENU //

	Menu(); // Constructor por Defecto //

	void set_Menu(); // Inicializa el Menú //
	void set_Estado_Menu(Estado_Menu estado); // Cambia el Estado del Menú //

	void draw_Menu(); // Muestra el Menú //

	void mouse_Menu(int mouse_X, int mouse_Y); // Movimiento del Ratón en el Menú //

	~Menu(); // Destructor //

	// MÉTODOS AUXILIARES DE LA CLASE MENU //

	// Función para obtener el estado actual del menú //

	Estado_Menu get_Estado_Menu() const { return Estado_Actual_Menu; } // Devuelve el Estado Actual del Menú //
	
	// Función auxiliar para dibujar texto usando una fuente bitmap.

	static void draw_BitmapText(const std::string &text, float x, float y) 
	{
		glRasterPos2f(x, y);
		for (char c : text) 
		{
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
		}
	}

private:
	
	// PARÁMETROS PRIVADOS DE LA CLASE MENU //

	// Botones del Menú Principal //
	std::vector<Boton> v_Botones_Main_Menu; // Vector de Botones del Menú Principal//

	// Botones del Menú de Ajustes //
	std::vector<Boton> v_Botones_Settings; // Vector de Botones del Menú de Ajustes //
	
	// Estado del Menú //
	Estado_Menu Estado_Actual_Menu; // Estado Actual del Menú //
};

#endif // MENU_H