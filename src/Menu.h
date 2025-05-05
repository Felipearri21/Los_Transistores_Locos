#pragma once

#ifndef MENU_H
#define MENU_H

// INCLUSI�N DE LIBRER�AS Y FICHEROS DE CABECERA //

// Inclusion de Librer�as Estandar //
#include <string>
#include <vector>

// Inclusion de Librer�a de OpenGL //
#include "freeglut.h"

// Inclusion de Ficheros de Encabezado Locales //
#include "Boton.h"

// DEFINICI�N DE CLASES Y ESTRUCTURAS //

// Clase que representa los posibles Estados del Men� //

enum class Estado_Menu
{
	MAIN_MENU, // Menu Principal
	AJEDREZ, // Estado en el que se ha Seleccionado el Modo de Juego Normal //
	ALAMOS, // Estado en el que se ha Seleccionado el Modo de Juego Los �lamos //
	SILVERMAN, // Estado en el que se ha Seleccionado el Modo de Juego Silverman 4x4 //
	TITLE_SCREEN, // Estado en el que aparece la Pantalla de T�tulo //
	GAME_OVER, // Estado en el que se ha terminado el Juego //
	SETTINGS, // Estado en el que se han cambiado los Ajustes del Juego //
	EXIT // Estado en el que se sale del Juego //
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

	void keyboard_Menu(unsigned char key); // Teclado en el Men� //

	void mouse_Menu(int mouse_X, int mouse_Y); // Movimiento del Rat�n en el Men� //

	// M�TODOS AUXILIARES DE LA CLASE MENU //

	// Funci�n para obtener el estado actual del men� //

	Estado_Menu get_Estado_Menu() const { return Estado_Actual_Menu; } // Devuelve el Estado Actual del Men� //

private:
	
	// PAR�METROS PRIVADOS DE LA CLASE MENU //

	// Botones del Men� Principal //

	Boton Boton_Ajedrez_Normal // Bot�n para el Modo de Juego Normal //	
	{
		11, // Identificador del Bot�n //
		"Ajedrez Normal", // Texto del Bot�n //
		Color{ 228, 204, 72 }, // Color del Bot�n //
		760, // Coordenada X del Bot�n //
		700, // Coordenada Y del Bot�n //
		400, // Ancho del Bot�n //
		50 // Altura del Bot�n //

	}; 

	Boton Boton_Los_Alamos // Bot�n para el Modo de Juego Los �lamos //
	{
		12,  // Identificador del Bot�n //
		"Los Alamos", // Texto del Bot�n //
		Color{ 228, 204, 72 }, // Color del Bot�n //
		760, // Coordenada X del Bot�n //
		620, // Coordenada Y del Bot�n //
		400, // Ancho del Bot�n //
		50 // Altura del Bot�n //
	};

	Boton Boton_Silverman_4x4 // Bot�n para el Modo de Juego Silverman 4x4 //
	{
		13, // Identificador del Bot�n //
		"Silverman 4x4", // Texto del Bot�n //
		Color{ 228, 204, 72 }, // Color del Bot�n //
		760, // Coordenada X del Bot�n //
		540, // Coordenada Y del Bot�n //
		400, // Ancho del Bot�n //
		50 // Altura del Bot�n //
	};

	Boton Boton_Ajustes // Bot�n para el Modo de Ajustes //
	{
		14, // Identificador del Bot�n //
		"Ajustes", // Texto del Bot�n //
		Color{ 228, 204, 72 }, // Color del Bot�n //
		760, // Coordenada X del Bot�n //
		460, // Coordenada Y del Bot�n //
		400, // Ancho del Bot�n //
		50 // Altura del Bot�n //
	};

	std::vector<Boton> v_Botones_Main_Menu
	{
		Boton_Ajedrez_Normal,
		Boton_Los_Alamos,
		Boton_Silverman_4x4,
		Boton_Ajustes
	};

	// Botones del Men� de Ajustes //

	Boton Boton_Subir_Volumen // Bot�n para Subir el Volumen //
	{
		21, // Identificador del Bot�n //
		"Subir Volumen", // Texto del Bot�n //
		Color{ 228, 204, 72 }, // Color del Bot�n //
		760, // Coordenada X del Bot�n //
		700, // Coordenada Y del Bot�n //
		400, // Ancho del Bot�n //
		50 // Altura del Bot�n //
	};

	Boton Boton_Bajar_Volumen // Bot�n para Bajar el Volumen //
	{
		22, // Identificador del Bot�n //
		"Bajar Volumen", // Texto del Bot�n //
		Color{ 228, 204, 72 }, // Color del Bot�n //
		760, // Coordenada X del Bot�n //
		620, // Coordenada Y del Bot�n //
		400, // Ancho del Bot�n //
		50 // Altura del Bot�n //
	};

	Boton Boton_Menu_Principal // Bot�n para Volver al Men� Principal //
	{
		23, // Identificador del Bot�n //
		"Menu Principal", // Texto del Bot�n //
		Color{ 228, 204, 72 }, // Color del Bot�n //
		760, // Coordenada X del Bot�n //
		540, // Coordenada Y del Bot�n //
		400, // Ancho del Bot�n //
		50 // Altura del Bot�n //
	};

	Boton Boton_Salir // Bot�n para Salir del Juego //
	{
		24, // Identificador del Bot�n //
		"Salir", // Texto del Bot�n //
		Color{ 228, 204, 72 }, // Color del Bot�n //
		760, // Coordenada X del Bot�n //
		460, // Coordenada Y del Bot�n //
		400, // Ancho del Bot�n //
		50 // Altura del Bot�n //
	};

	std::vector<Boton> v_Botones_Settings
	{
		Boton_Subir_Volumen,
		Boton_Bajar_Volumen,
		Boton_Menu_Principal,
		Boton_Salir
	};
	
	// Estado del Men� //

	Estado_Menu Estado_Actual_Menu; // Estado Actual del Men� //
};

#endif // MENU_H