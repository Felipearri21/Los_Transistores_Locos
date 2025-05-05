// INCLUSIÓN DE LIBRERÍAS Y FICHEROS DE CABECERA //

// Inclusion de Librerías Estandar //
#include <iostream>

// Inclusion de Librería de OpenGL //
#include "freeglut.h"

// Inclusion de Librería de ETSIDI //
#include "ETSIDI.h"

// Inclusion de Ficheros de Encabezado Locales //
#include "menu.h"
#include "Variables_Globales.h"

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

	glutInit(&argc, argv); // Inicializa GLUT y procesa los parámetros de la línea de comandos //

	// CREAR Y CONFIGURAR LA VENTANA //

	glutInitWindowSize(window_Width, window_Height); // Establece el tamaño de la ventana a 1920x1080 píxeles //

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Establece el modo de visualización. (doble buffer, RGB, profundidad) //

	glutCreateWindow("Los Transistores Locos"); // Crea una ventana con el título "Los Transistores Locos" //

	glutFullScreen(); // Pone la ventana en modo pantalla completa //

	// Establece el color de fondo //

	glClearColor(1, 1, 1, 1);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT0);

	// Configura la proyección en perspectiva para la escena 3D //

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(40.0, (float)1920 / 1080, 0.1, 150.0);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();


	// REGISTRAR LOS CALLBAKS ("Cuando pase esto, llama a esta función") // 

	glutDisplayFunc(OnDraw); // Llama a la función OnDraw() para dibujar //

	glutTimerFunc(25, OnTimer, 0); // Llama a la función OnTimer() para la animación //

	glutKeyboardFunc(OnKeyboardDown); // Llama a la función OnKeyboardDown() para el teclado //

	glutSpecialFunc(OnSpecialKeyboardDown); // Llama a la función OnSpecialKeyboardDown() para el teclado especial //

	glutMouseFunc(OnMouse); // Llama a la función OnMouse() para el ratón //

	glutReshapeFunc(OnReshape); // Llama a la función OnReshape() para el cambio de tamaño de la ventana //

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
		//  Quitar el offset del viewport (area de visualizacion) //
		int adjusted_X = x - viewport_X;
		int adjusted_Y = y - viewport_Y;

		// Invertir la coordenada Y (en GLUT el origen esta en la parte superior) //
		adjusted_Y = viewport_Height - adjusted_Y;

		// Escalar las coordenadas reales a la resolución virtual.
		float scale_X = virtual_Width / viewport_Width;
		float scale_Y = virtual_Height / viewport_Height;
		int virtual_X = (int)(adjusted_X * scale_X);
		int virtual_Y = (int)(adjusted_Y * scale_Y);

		Menu_1.mouse_Menu(virtual_X, virtual_Y);

	}

	glutPostRedisplay(); // SIEMPRE SE PONE ESTA LINEA PARA REDIBUJAR //
}

void OnReshape(int w, int h)
{
	window_Width = w;
	window_Height = h;

	float window_Aspect = (float)w / h;
	float virtual_Aspect = virtual_Width / virtual_Height;

	if (window_Aspect > virtual_Aspect)
	{
		// La ventana es más ancha que la virtual //

		viewport_Height = h;
		viewport_Width = (int)(h * virtual_Aspect);
		viewport_X = (w - viewport_Width) / 2;
		viewport_Y = 0;
	}
	else
	{
		// La ventana es más alta (o relación igual).
		viewport_Width = w;
		viewport_Height = (int)(w / virtual_Aspect);
		viewport_X = 0;
		viewport_Y = (h - viewport_Height) / 2;
	}

	glViewport(viewport_X, viewport_Y, viewport_Width, viewport_Height);

	// Configura la proyección ortográfica usando la resolución virtual.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, virtual_Width, 0, virtual_Height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutPostRedisplay();
}




// FIN DEL PROGRAMA //