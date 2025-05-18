// INCLUSION DE FICHEROS Y LIBRERIAS //

// Librerias Estandar //
#include <iostream>

// Libreria ETSIDI //
#include "ETSIDI.h"

// Ficheros Locales //

#include "Boton.h"
#include "Funciones_Globales.h"

// METODOS DE LA CLASE //


Boton::Boton(int id, std::string texto, Color color, int x, int y, int ancho, int altura)
    : ID_Boton(id), Texto_Boton(texto), Color_Boton(color), X_Boton(x), Y_Boton(y), Ancho_Boton(ancho), Altura_Boton(altura)
{
    std::cout << "Boton " << Texto_Boton << " creado" << std::endl;
}

void Boton::draw_Boton()
{
    Color actual = Color_Boton;
    int ancho = Ancho_Boton;
    int alto = Altura_Boton;
    int x = X_Boton;
    int y = Y_Boton;

    if (hovered)
    {
        actual.set_Color(255, 255, 100); // Color más claro al hacer hover
        ancho += 20;
        alto += 10;
        x -= 10;
        y -= 5;
    }

    actual.implement_Color();
    glBegin(GL_QUADS);
    glVertex2i(x, y);
    glVertex2i(x + ancho, y);
    glVertex2i(x + ancho, y + alto);
    glVertex2i(x, y + alto);
    glEnd();

    glColor3f(0, 0, 0);
    int anchoTexto = calculate_Ancho_Texto(Texto_Boton);
    int altoTexto = 20;
    int x_Texto = x + (ancho - anchoTexto) / 2;
    int y_Texto = y + (alto - altoTexto) / 2;
    draw_BitmapText(Texto_Boton, x_Texto, y_Texto);
}

bool Boton::contact_Boton(int mouse_X, int mouse_Y) const
{
    return (mouse_X >= X_Boton && mouse_X <= X_Boton + Ancho_Boton &&
        mouse_Y >= Y_Boton && mouse_Y <= Y_Boton + Altura_Boton);
}

void Boton::sound_Boton(int mouse_X, int mouse_Y) const
{
    if (contact_Boton(mouse_X, mouse_Y))
    {
        ETSIDI::play("sonidos/sound_effect_Click.wav");
    }
}

void Boton::set_ColorRGB(int r, int g, int b)
{
    Color_Boton.set_Color(r, g, b);
}
