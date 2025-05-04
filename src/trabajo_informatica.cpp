// INCLUSION DE LIBRERIAS Y FICHEROS DE CABECERA //

// Inclusion de Librerias Estandar //
#include <iostream>

// Inclusion de Libreria de OpenGL //
#include "freeglut.h"

// Inclusion de Libreria de ETSIDI //
#include "ETSIDI.h"

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

// VARIABLES GLOBALES //

int windowWidth = 800;
int windowHeight = 600;

// PROGRAMA PRINCIPAL //

int main(int argc, char* argv[])
{
	// INICIALIZAR EL GESTOR DE VENTANAS DE GLUT //

	glutInit(&argc, argv); // Inicializa GLUT y procesa los parámetros de la linea de comandos //

	// CREAR Y CONFIGURAR LA VENTANA //

	glutInitWindowSize(windowWidth, windowHeight); // Establece el tamaño de la ventana a 800x600 pixeles //

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Establece el modo de visualizacion. (doble buffer, RGB, profundidad) //

	glutCreateWindow("Los Transistores Locos"); // Crea una ventana con el titulo "Los Transistores Locos" //

	// Establece el color de fondo //

	glClearColor(1, 1, 1, 1);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT0);

	// Configura la proyeccion en perspectiva para la escena 3D //

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(40.0, static_cast<float>(windowWidth) / windowHeight, 0.1, 150.0);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();


	// REGISTRAR LOS CALLBAKS ("Cuando pase esto, llama a esta funcion") // 

	glutDisplayFunc(OnDraw); // Llama a la funcion OnDraw() para dibujar //

	glutTimerFunc(25, OnTimer, 0); // Llama a la funcion OnTimer() para la animacion //

	glutKeyboardFunc(OnKeyboardDown); // Llama a la funcion OnKeyboardDown() para el teclado //

	glutSpecialFunc(OnSpecialKeyboardDown); // Llama a la funcion OnSpecialKeyboardDown() para el teclado especial //

	glutMouseFunc(OnMouse); // Llama a la funcion OnMouse() para el raton //

	glutReshapeFunc(OnReshape); // Llama a la funcion OnReshape() para el cambio de tamaño de la ventana //

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

	Menu_1.draw_Menu(); // Funcion dentro del Mundo que dibuja los objetos //

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

	Menu_1.keyboard_Menu(key); // Funcion dentro del Mundo que procesa el teclado //

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
		// Mapear las coordenadas del mouse desde el tamaño real de la ventana al sistema logico 800x600 //
		int adjusted_X = static_cast<int>(x * (800.0 / windowWidth));
		int adjusted_Y = static_cast<int>((windowHeight - y) * (600 / windowHeight));

		// Se procesa el clic en el menu utilizando las coordenadas ajustadas //
		Menu_1.mouse_Menu(adjusted_X, adjusted_Y);
	}

	glutPostRedisplay(); // SIEMPRE SE PONE ESTA LINEA PARA REDIBUJAR //
}

void OnReshape(int w, int h)
{
	windowWidth = w; // Actualiza el ancho de la ventana //
	windowHeight = h; // Actualiza la altura de la ventana //

	glViewport(0, 0, w, h); // Establece el area de visualización //

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, static_cast<float>(w) / h, 0.1, 150.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutPostRedisplay(); // SIEMPRE SE PONE ESTA LINEA PARA REDIBUJAR //
}



// FIN DEL PROGRAMA //