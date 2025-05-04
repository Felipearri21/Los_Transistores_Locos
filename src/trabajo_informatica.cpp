// INCLUSIÓN DE LIBRERÍAS Y FICHEROS DE CABECERA //

// Inclusion de Librerías Estandar //
#include <iostream>

// Inclusion de Librería de OpenGL //
#include "freeglut.h"

// Inclusion de Ficheros de Encabezado Locales //
#include "menu.h"

// DECLARACION DE CLASES //

Menu Menu_1; // Objeto de la clase Menu. //

// PROTOTIPOS DE LAS FUNCIONES DE GLUT //

void OnDraw(void); // Funcion de dibujo //

void OnTimer(int value); // Funcion de animacion //

void OnKeyboardDown(unsigned char key, int x, int y); // Funcion de teclado //

void OnSpecialKeyboardDown(int key, int x, int y); // Funcion de teclado especial //

void OnMouse(int button, int state, int x, int y); // Funcion de raton //

void OnReshape(int w, int h); // Funcion de cambio de tamaño de ventana //

// PROGRAMA PRINCIPAL //

int main(int argc, char* argv[])
{
	// INICIALIZAR EL GESTOR DE VENTANAS DE GLUT //

	glutInit(&argc, argv); // Inicializa GLUT y procesa los parámetros de la línea de comandos. //

	// CREAR Y CONFIGURAR LA VENTANA //

	glutInitWindowSize(800, 600); // Establece el tamaño de la ventana a 800x600 píxeles. //

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Establece el modo de visualización. (doble buffer, RGB, profundidad). //

	glutCreateWindow("Los Transistores Locos"); // Crea una ventana con el título "MiJuego". //

	// Establece el color de fondo //

	glClearColor(1, 1, 1, 1);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT0);

	// Configura la proyección en perspectiva para la escena 3D.

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(40.0, 800.0 / 600.0, 0.1, 150.0);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();


	// REGISTRAR LOS CALLBAKS ("Cuando pase esto, llama a esta función".) // 

	glutDisplayFunc(OnDraw); // Llama a la función OnDraw() para dibujar. //

	glutTimerFunc(25, OnTimer, 0); // Llama a la función OnTimer() para la animación. //

	glutKeyboardFunc(OnKeyboardDown); // Llama a la función OnKeyboardDown() para el teclado. //

	glutSpecialFunc(OnSpecialKeyboardDown); // Llama a la función OnSpecialKeyboardDown() para el teclado especial. //

	glutMouseFunc(OnMouse); // Llama a la función OnMouse() para el ratón. //

	glutReshapeFunc(OnReshape); // Llama a la función OnReshape() para el cambio de tamaño de la ventana. //

	// INICIALIZACIONES //

	// BUCLE PRINCIPAL //

	glutMainLoop();

	return 0;
}

// DEFINICIONES DE FUNCIONES DE GLUT //

void OnDraw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //SIEMPRE SE PONE ESTA LINEA ANTES DE DIBUJAR//

	// CODIGO DEL DIBUJO //

	Menu_1.draw_Menu(); // Funcion dentro del Mundo que dibuja los objetos. //

	glutSwapBuffers(); //NUNCA SE BORRA ESTA LINEA Y NO SE PONE NADA DESPUES DE ELLA//
}

void OnTimer(int value)
{
	// CODIGO DE LA ANIMACION //

	glutTimerFunc(25, OnTimer, 0); //Le decimos que dentro de 25ms llame 1 vez a la funcion OnTimer() //

	glutPostRedisplay(); // SIEMPRE SE PONE ESTA LINEA PARA REDIBUJAR //
}

void OnKeyboardDown(unsigned char key, int x, int y)
{
	// CODIGO DEL TECLADO //

	glutPostRedisplay(); // SIEMPRE SE PONE ESTA LINEA PARA REDIBUJAR //
}

void OnSpecialKeyboardDown(int key, int x, int y)
{
	// CODIGO DEL TECLADO ESPECIAL //

	glutPostRedisplay(); // SIEMPRE SE PONE ESTA LINEA PARA REDIBUJAR //
}

void OnMouse(int button, int state, int x, int y)
{
	// CODIGO DEL RATON //

	if (state == GLUT_DOWN)
	{
		// Convierte la coordenada Y (GLUT recibe Y desde la parte superior) a un sistema con (0,0) en la esquina inferior izquierda //
		int mouseY = 600 - y; // Dado que la ventana es de 600 pixeles de alto.

		Menu_1.mouse_Menu(x, mouseY);
	}

	glutPostRedisplay(); // SIEMPRE SE PONE ESTA LINEA PARA REDIBUJAR //
}

void OnReshape(int w, int h)
{
	glViewport(0, 0, w, h);

	// Actualiza la proyección en perspectiva para la escena 3D.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, (float)w / (float)h, 0.1, 150.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutPostRedisplay();
}


// FIN DEL PROGRAMA //