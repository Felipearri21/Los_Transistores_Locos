#pragma once

#ifndef MENU_H
#define MENU_H

// INCLUSIÓN DE LIBRERÍAS Y FICHEROS DE CABECERA //

// Inclusion de Librerías Estandar //
#include <string>
#include <vector>

// Inclusion de Librería de OpenGL //
#include "freeglut.h"

// Inclusion de Ficheros de Encabezado Locales //
#include "Boton.h"

// DEFINICIÓN DE CLASES Y ESTRUCTURAS //

// Clase que representa los posibles Estados del Menú //

enum class Estado_Menu
{
	MAIN_MENU, // Menu Principal
	AJEDREZ, // Estado en el que se ha Seleccionado el Modo de Juego Normal //
	ALAMOS, // Estado en el que se ha Seleccionado el Modo de Juego Los Álamos //
	SILVERMAN, // Estado en el que se ha Seleccionado el Modo de Juego Silverman 4x4 //
	TITLE_SCREEN, // Estado en el que aparece la Pantalla de Título //
	GAME_OVER, // Estado en el que se ha terminado el Juego //
	SETTINGS, // Estado en el que se han cambiado los Ajustes del Juego //
	EXIT // Estado en el que se sale del Juego //
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

	void keyboard_Menu(unsigned char key); // Teclado en el Menú //

	void mouse_Menu(int mouse_X, int mouse_Y); // Movimiento del Ratón en el Menú //

	// MÉTODOS AUXILIARES DE LA CLASE MENU //

	// Función para obtener el estado actual del menú //

	Estado_Menu get_Estado_Menu() const { return Estado_Actual_Menu; } // Devuelve el Estado Actual del Menú //

private:
	
	// PARÁMETROS PRIVADOS DE LA CLASE MENU //

	// Botones del Menú Principal //

	Boton Boton_Ajedrez_Normal // Botón para el Modo de Juego Normal //	
	{
		11, // Identificador del Botón //
		"Ajedrez Normal", // Texto del Botón //
		Color{ 228, 204, 72 }, // Color del Botón //
		760, // Coordenada X del Botón //
		700, // Coordenada Y del Botón //
		400, // Ancho del Botón //
		50 // Altura del Botón //

	}; 

	Boton Boton_Los_Alamos // Botón para el Modo de Juego Los Álamos //
	{
		12,  // Identificador del Botón //
		"Los Alamos", // Texto del Botón //
		Color{ 228, 204, 72 }, // Color del Botón //
		760, // Coordenada X del Botón //
		620, // Coordenada Y del Botón //
		400, // Ancho del Botón //
		50 // Altura del Botón //
	};

	Boton Boton_Silverman_4x4 // Botón para el Modo de Juego Silverman 4x4 //
	{
		13, // Identificador del Botón //
		"Silverman 4x4", // Texto del Botón //
		Color{ 228, 204, 72 }, // Color del Botón //
		760, // Coordenada X del Botón //
		540, // Coordenada Y del Botón //
		400, // Ancho del Botón //
		50 // Altura del Botón //
	};

	Boton Boton_Ajustes // Botón para el Modo de Ajustes //
	{
		14, // Identificador del Botón //
		"Ajustes", // Texto del Botón //
		Color{ 228, 204, 72 }, // Color del Botón //
		760, // Coordenada X del Botón //
		460, // Coordenada Y del Botón //
		400, // Ancho del Botón //
		50 // Altura del Botón //
	};

	std::vector<Boton> v_Botones_Main_Menu
	{
		Boton_Ajedrez_Normal,
		Boton_Los_Alamos,
		Boton_Silverman_4x4,
		Boton_Ajustes
	};

	// Botones del Menú de Ajustes //

	Boton Boton_Subir_Volumen // Botón para Subir el Volumen //
	{
		21, // Identificador del Botón //
		"Subir Volumen", // Texto del Botón //
		Color{ 228, 204, 72 }, // Color del Botón //
		760, // Coordenada X del Botón //
		700, // Coordenada Y del Botón //
		400, // Ancho del Botón //
		50 // Altura del Botón //
	};

	Boton Boton_Bajar_Volumen // Botón para Bajar el Volumen //
	{
		22, // Identificador del Botón //
		"Bajar Volumen", // Texto del Botón //
		Color{ 228, 204, 72 }, // Color del Botón //
		760, // Coordenada X del Botón //
		620, // Coordenada Y del Botón //
		400, // Ancho del Botón //
		50 // Altura del Botón //
	};

	Boton Boton_Menu_Principal // Botón para Volver al Menú Principal //
	{
		23, // Identificador del Botón //
		"Menu Principal", // Texto del Botón //
		Color{ 228, 204, 72 }, // Color del Botón //
		760, // Coordenada X del Botón //
		540, // Coordenada Y del Botón //
		400, // Ancho del Botón //
		50 // Altura del Botón //
	};

	Boton Boton_Salir // Botón para Salir del Juego //
	{
		24, // Identificador del Botón //
		"Salir", // Texto del Botón //
		Color{ 228, 204, 72 }, // Color del Botón //
		760, // Coordenada X del Botón //
		460, // Coordenada Y del Botón //
		400, // Ancho del Botón //
		50 // Altura del Botón //
	};

	std::vector<Boton> v_Botones_Settings
	{
		Boton_Subir_Volumen,
		Boton_Bajar_Volumen,
		Boton_Menu_Principal,
		Boton_Salir
	};
	
	// Estado del Menú //

	Estado_Menu Estado_Actual_Menu; // Estado Actual del Menú //
};

#endif // MENU_H