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
#include "Gestor_Audio.h"
#include "Variables_Globales.h"

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

// Grupo A: Botones de modos de juego
	Boton Boton_Ajedrez_Normal  // Bot�n para el Modo de Juego Normal
	{
		11,                     // Identificador del Bot�n
		"Ajedrez Normal",       // Texto del Bot�n
		Color{228, 204, 72},     // Color del Bot�n
		195,                    // X (margen izquierdo)
		100,                    // Y (todos en Y = 100)
		250,                    // Ancho del Bot�n
		50                      // Altura del Bot�n
	};

	Boton Boton_Los_Alamos  // Bot�n para el Modo de Juego Los �lamos
	{
		12,
		"Los Alamos",
		Color{228, 204, 72},
		515,                    // X = 110 + 250 + 20
		100,
		250,
		50
	};

	Boton Boton_Silverman_4x4  // Bot�n para el Modo de Juego Silverman 4x4
	{
		13,
		"Silverman 4x4",
		Color{228, 204, 72},
		835,                    // X = 380 + 250 + 20
		100,
		250,
		50
	};

	Boton Boton_Ajustes  // Bot�n para el Modo de Ajustes
	{
		14,
		"Ajustes",
		Color{228, 204, 72},
		1155,                    // X = 650 + 250 + 20
		100,
		250,
		50
	};

	// Grupo B: Botones del �rea de audio
	// Se asume que el �rea de audio comienza en X = 1190

	// Bot�n central que muestra la canci�n actual.
	// Se coloca en la fila superior (Y = 100) y tendr� ancho 310 (150 + 10 + 150).
	Boton Boton_Audio_Current
	{
		16,
		"Ninguna",              // Texto inicial (se actualizar� en tiempo de ejecuci�n)
		Color{228, 204, 72},
		1445,                   // X del grupo de audio
		160,                    // Y (fila superior)
		310,                    // Ancho = 150 + 10 + 150
		50                      // Altura
	};

	// Los botones "previous" y "next" se colocan en una fila inferior, debajo del bot�n central.
	// Se utilizan anchos m�nimos de 150, con separaci�n interna de 10.
	Boton Boton_Audio_Previous
	{
		15,
		"<-",
		Color{228, 204, 72},
		1445,                   // X (igual que el inicio del grupo de audio)
		100,                    // Y = 100 + 50 + 10 (fila inferior)
		150,                    // Ancho m�nimo
		50
	};

	Boton Boton_Audio_Next
	{
		17,
		"->",
		Color{228, 204, 72},
		1605,        // X = 1190 + 150 + 10 = 1350
		100,                    // Y (fila inferior)
		150,                    // Ancho m�nimo
		50
	};

	// Vector con todos los botones del men�
	std::vector<Boton> v_Botones_Main_Menu
	{
		Boton_Ajedrez_Normal,
		Boton_Los_Alamos,
		Boton_Silverman_4x4,
		Boton_Ajustes,
		Boton_Audio_Current,    // Se dibuja el bot�n central para el audio en la fila superior
		Boton_Audio_Previous,   // Debajo, se colocan los botones de "previous" y "next"
		Boton_Audio_Next
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