//INCLUSION DE FICHEROS Y LIBRERIAS //

// Librerias de OpenGL //
#include <freeglut.h>

// Ficheros Locales //

#include "Menu.h"
#include "Gestor_Audio.h"
#include "Variables_Globales.h"

// DECLARACION DE CLASES //

Menu Menu_1;
Gestor_Audio Gestor_Audio_1;

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

    Menu_1.draw_Menu();

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