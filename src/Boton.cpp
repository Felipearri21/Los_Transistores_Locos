// INCLUSI�N DE LIBRER�AS Y FICHEROS DE CABECERA //

// Inclusion de Librer�as Estandar //
#include <iostream>

// Inclusion de Librer�a de ETSIDI //
#include "ETSIDI.h"

// Inclusion de Ficheros de Encabezado Locales //
#include "Boton.h"
#include "Funciones_Globales.h"


// CONSTRUCTORES //

Boton::Boton
(
    int id,
    std::string texto,
    Color color,
    int x,
    int y,
    int ancho,
    int altura
    )
{
	// Inicializa los par�metros del bot�n.
	ID_Boton = id;
	Texto_Boton = texto;
	Color_Boton = color;
	X_Boton = x;
	Y_Boton = y;
	Ancho_Boton = ancho;
	Altura_Boton = altura;

	// Mensaje de depuraci�n para confirmar carga de botones.
	std::cout << "Boton " << Texto_Boton << " creado" << std::endl;
}

// METODOS DE LA CLASE BOTON //

// Muestra el Bot�n //

void Boton::draw_Boton()
{
    // Fondo del bot�n.
	Color_Boton.implement_Color(); // Establece el color del bot�n //
    glBegin(GL_QUADS);
    glVertex2i(X_Boton, Y_Boton);
    glVertex2i(X_Boton + Ancho_Boton, Y_Boton);
    glVertex2i(X_Boton + Ancho_Boton, Y_Boton + Altura_Boton);
    glVertex2i(X_Boton, Y_Boton + Altura_Boton);
    glEnd();

    // Dibuja el texto //
    glColor3f(0, 0, 0); // Texto de color negro //

    int anchoTexto = calculate_Ancho_Texto(Texto_Boton);
    // Si la altura del texto es constante, por ejemplo 20 p�xeles, o si tienes:
    // int altoTexto = calculate_Alto_Texto(Texto_Boton);
    int altoTexto = 20; // Valor de ejemplo

    // Calcular la posici�n para centrar el texto en el bot�n:
    int x_Texto = X_Boton + (Ancho_Boton - anchoTexto) / 2;
    int y_Texto = Y_Boton + (Altura_Boton - altoTexto) / 2;

    draw_BitmapText(Texto_Boton, x_Texto, y_Texto);
}

bool Boton::contact_Boton(int mouse_X, int mouse_Y)const
{
    // Verifica si el rat�n est� dentro de los l�mites del bot�n.
    
    return 
        (
        mouse_X >= X_Boton && mouse_X <= X_Boton + Ancho_Boton &&
        mouse_Y >= Y_Boton && mouse_Y <= Y_Boton + Altura_Boton
        );
}

void Boton::sound_Boton(int mouse_X, int mouse_Y)const
{
    if (contact_Boton(mouse_X, mouse_Y) == true)
    {
        ETSIDI::play("sonidos/sound_effect_Click.wav");
    }
}