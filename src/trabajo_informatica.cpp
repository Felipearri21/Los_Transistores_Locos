//INCLUSION DE FICHEROS Y LIBRERIAS //

// Librerias de OpenGL //
#include <freeglut.h>

// Ficheros Locales //

#include "Menu.h"
#include "Gestor_Audio.h"
#include "Variables_Globales.h"
#include "tablero.h"
#include "Funciones_Globales.h"

// DECLARACION DE CLASES //

Menu Menu_1;
Gestor_Audio Gestor_Audio_1;
Tablero* tablero;
Estado_Menu estado_anterior = Estado_Menu::TITLE_SCREEN;

// PROTOTIPOS DE FUNCIONES DE GLUT //

void OnDisplay();
void OnReshape(int width, int height);
void OnKeyboard(unsigned char key, int x, int y);
void OnMouse(int button, int state, int x, int y);
void OnPassiveMouseMotion(int x, int y);

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(virtual_Width / 2, virtual_Height / 2);
    glutCreateWindow("Los Transistores Locos presenta: Ajedrez Edition");

    glutDisplayFunc(OnDisplay);
    glutReshapeFunc(OnReshape);
    glutKeyboardFunc(OnKeyboard);
    glutMouseFunc(OnMouse);
    glutPassiveMotionFunc(OnPassiveMouseMotion);
	glutFullScreen();   

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Gestor_Audio::set_Gestor_Audio();
    Menu_1.set_Fondo("imagenes/menu_principal_(1920x1080).png");

    glutMainLoop();
    return 0;
}

void OnDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Gestor_Audio::update_Musica(Menu_1.get_Estado_Menu());

    Estado_Menu estado_actual = Menu_1.get_Estado_Menu();

    // Si se entra por primera vez en un modo de juego, crea el tablero correspondiente
    if ((estado_actual == Estado_Menu::AJEDREZ ||
        estado_actual == Estado_Menu::ALAMOS ||
        estado_actual == Estado_Menu::SILVERMAN) &&
        estado_actual != estado_anterior)
    {
        // Si ya había un tablero, lo borramos
        if (tablero) {
            delete tablero;
            tablero = nullptr;
        }

        switch (estado_actual) {
        case Estado_Menu::AJEDREZ:
            tablero = new Tablero(ModoJuego::NORMAL);
            break;
        case Estado_Menu::ALAMOS:
            tablero = new Tablero(ModoJuego::ALAMOS);
            break;
        case Estado_Menu::SILVERMAN:
            tablero = new Tablero(ModoJuego::SILVERMAN);
            break;
        default:
            break;
        }

        // Establecer fondo visual para todos los modos de juego
        Menu_1.set_Fondo("imagenes/fondo_juego_(1920x1080).png");
    }

    // Si está en un modo de juego, dibuja el tablero
    if (estado_actual == Estado_Menu::AJEDREZ ||
        estado_actual == Estado_Menu::ALAMOS ||
        estado_actual == Estado_Menu::SILVERMAN)
    {
        Menu_1.draw_Fondo(Menu_1.get_Fondo());

        if (tablero)
            tablero->dibujarTablero();

        // Mostrar el texto del modo actual arriba
        std::string texto;
        switch (estado_actual) {
        case Estado_Menu::AJEDREZ: texto = "AJEDREZ NORMAL"; break;
        case Estado_Menu::ALAMOS: texto = "LOS ALAMOS 6x6"; break;
        case Estado_Menu::SILVERMAN: texto = "SILVERMAN 4x4"; break;
        default: break;
        }

        int ancho = calculate_Ancho_Texto(texto, GLUT_BITMAP_HELVETICA_18);
        int x = (virtual_Width - ancho) / 2;
        int y = virtual_Height - 80;
        glColor3f(1.0f, 1.0f, 0.6f);
        draw_BitmapText(texto, x, y);
    }
    else {
        // Si vuelve al menú, borra el tablero si existe
        if (tablero) {
            delete tablero;
            tablero = nullptr;
        }

        Menu_1.draw_Menu();
    }

    estado_anterior = estado_actual;

    glutSwapBuffers();
}

void OnReshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, virtual_Width, 0, virtual_Height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OnKeyboard(unsigned char key, int x, int y)
{
    Menu_1.keyboard_Menu(key);
    glutPostRedisplay();
}

void OnMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int realWidth = glutGet(GLUT_WINDOW_WIDTH);
        int realHeight = glutGet(GLUT_WINDOW_HEIGHT);
        float escalaX = virtual_Width / static_cast<float>(realWidth);
        float escalaY = virtual_Height / static_cast<float>(realHeight);

        int x_virtual = static_cast<int>(x * escalaX);
        int y_virtual = static_cast<int>((realHeight - y) * escalaY);

        Menu_1.mouse_Menu(x_virtual, y_virtual);

        glutPostRedisplay();
    }
}

void OnPassiveMouseMotion(int x, int y)
{
    int realWidth = glutGet(GLUT_WINDOW_WIDTH);
    int realHeight = glutGet(GLUT_WINDOW_HEIGHT);
    float escalaX = virtual_Width / static_cast<float>(realWidth);
    float escalaY = virtual_Height / static_cast<float>(realHeight);

    int x_virtual = static_cast<int>(x * escalaX);
    int y_virtual = static_cast<int>((realHeight - y) * escalaY);

    Menu_1.actualizar_Hover(x_virtual, y_virtual);

    glutPostRedisplay();
}

// Fin del código