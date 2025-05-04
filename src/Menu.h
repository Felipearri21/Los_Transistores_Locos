#pragma once

#ifndef MENU_H
#define MENU_H

// INCLUSION DE LIBRERIAS Y FICHEROS DE CABECERA //

// Inclusion de Librerias Estandar //
#include <string>
#include <vector>

// Inclusion de Libreria de OpenGL //
#include "freeglut.h"

// Inclusion de Ficheros de Encabezado Locales //
#include "Boton.h"

// DEFINICI�N DE CLASES Y ESTRUCTURAS //

// Clase que representa los posibles Estados del Menu //

enum class Estado_Menu
{
	MAIN_MENU, // Menu Principal
	AJEDREZ, // Estado en el que se ha Seleccionado el Modo de Juego Normal //
	ALAMOS, // Estado en el que se ha Seleccionado el Modo de Juego Los Alamos //
	SILVERMAN, // Estado en el que se ha Seleccionado el Modo de Juego Silverman 4x4 //
	TITLE_SCREEN, // Estado en el que aparece la Pantalla de Titulo //
	GAME_OVER, // Estado en el que se ha terminado el Juego //
	SETTINGS, // Estado en el que se han cambiado los Ajustes del Juego //
	EXIT // Estado en el que se sale del Juego //
};

// Clase que representa el Menu //

class Menu
{
public:

	// METODOS PRINCIPALES DE LA CLASE MENU //

	Menu(); // Constructor por Defecto //

	void set_Menu(); // Inicializa el Menu //
	void set_Estado_Menu(Estado_Menu estado); // Cambia el Estado del Menu //

	void draw_Menu(); // Muestra el Menu //

	void keyboard_Menu(unsigned char key); // Teclado en el Menu //

	void mouse_Menu(int mouse_X, int mouse_Y); // Movimiento del Raton en el Menu //

	// METODOS AUXILIARES DE LA CLASE MENU //

	// Funcion para obtener el estado actual del menu //

	Estado_Menu get_Estado_Menu() const { return Estado_Actual_Menu; } // Devuelve el Estado Actual del Menu //

	// Funcion auxiliar para dibujar texto usando una fuente bitmap  (Se puede incluir en un fichero externo de funciones) //

	static void draw_BitmapText(const std::string& text, float x, float y)
	{
		glRasterPos2f(x, y);
		for (char c : text)
		{
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
		}
	}

private:

	// PARAMETROS PRIVADOS DE LA CLASE MENU //

	// Botones del Menu Principal //

	Boton Boton_Ajedrez_Normal // Boton para el Modo de Juego Normal //	
	{
		11, // Identificador del Boton //
		"Ajedrez Normal", // Texto del Boton //
		Color{ 228, 204, 72 }, // Color del Boton //
		200, // Coordenada X del Boton //
		400, // Coordenada Y del Boton //
		400, // Ancho del Boton //
		50 // Altura del Boton //

	};

	Boton Boton_Los_Alamos // Boton para el Modo de Juego Los Alamos //
	{
		12,  // Identificador del Boton //
		"Los Alamos", // Texto del Boton //
		Color{ 228, 204, 72 }, // Color del Boton //
		200, // Coordenada X del Boton //
		330, // Coordenada Y del Boton //
		400, // Ancho del Boton //
		50 // Altura del Boton //
	};

	Boton Boton_Silverman_4x4 // Boton para el Modo de Juego Silverman 4x4 //
	{
		13, // Identificador del Boton //
		"Silverman 4x4", // Texto del Boton //
		Color{ 228, 204, 72 }, // Color del Boton //
		200, // Coordenada X del Boton //
		260, // Coordenada Y del Boton //
		400, // Ancho del Boton //
		50 // Altura del Boton //
	};

	Boton Boton_Ajustes // Boton para el Modo de Ajustes //
	{
		14, // Identificador del Boton //
		"Ajustes", // Texto del Boton //
		Color{ 228, 204, 72 }, // Color del Boton //
		200, // Coordenada X del Boton //
		190, // Coordenada Y del Boton //
		400, // Ancho del Boton //
		50 // Altura del Boton //
	};

	std::vector<Boton> v_Botones_Main_Menu
	{
		Boton_Ajedrez_Normal,
		Boton_Los_Alamos,
		Boton_Silverman_4x4,
		Boton_Ajustes
	};

	// Botones del Menu de Ajustes //

	Boton Boton_Subir_Volumen // Boton para Subir el Volumen //
	{
		21, // Identificador del Boton //
		"Subir Volumen", // Texto del Boton //
		Color{ 228, 204, 72 }, // Color del Boton //
		200, // Coordenada X del Boton //
		400, // Coordenada Y del Boton //
		400, // Ancho del Boton //
		50 // Altura del Boton //
	};

	Boton Boton_Bajar_Volumen // Boton para Bajar el Volumen //
	{
		22, // Identificador del Boton //
		"Bajar Volumen", // Texto del Boton //
		Color{ 228, 204, 72 }, // Color del Boton //
		200, // Coordenada X del Boton //
		330, // Coordenada Y del Boton //
		400, // Ancho del Boton //
		50 // Altura del Boton //
	};

	Boton Boton_Menu_Principal // Boton para Volver al Menu Principal //
	{
		23, // Identificador del Boton //
		"Menu Principal", // Texto del Boton //
		Color{ 228, 204, 72 }, // Color del Boton //
		200, // Coordenada X del Boton //
		260, // Coordenada Y del Boton //
		400, // Ancho del Boton //
		50 // Altura del Boton //
	};

	Boton Boton_Salir // Boton para Salir del Juego //
	{
		24, // Identificador del Boton //
		"Salir", // Texto del Boton //
		Color{ 228, 204, 72 }, // Color del Boton //
		200, // Coordenada X del Boton //
		190, // Coordenada Y del Boton //
		400, // Ancho del Boton //
		50 // Altura del Boton //
	};

	std::vector<Boton> v_Botones_Settings
	{
		Boton_Subir_Volumen,
		Boton_Bajar_Volumen,
		Boton_Menu_Principal,
		Boton_Salir
	};

	// Estado del Menu //

	Estado_Menu Estado_Actual_Menu; // Estado Actual del Menu //
};

#endif // MENU_H