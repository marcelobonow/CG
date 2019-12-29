
#if _MSC_VER
#include <Windows.h>
#define _USE_MATH_DEFINES
#endif
#include <cmath>
#include <iostream>
#include <fstream>
#include "GL/gl.h" 
#include "GL/glu.h" 
#include "GL/glut.h"

#define WINDOWWIDTH 500
#define WINDOWHEIGHT 500
#define WINDOWSIZE 500
#define TAMQUADRADO 50
#define POSINICIAL 20

void DrawLoop();
void ResizeWindow(GLsizei, GLsizei);
void KeyboardInput(unsigned char, int, int);
void MouseInput(int button, int x, int y, int unknown);
void Inicializa(void);

int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WINDOWWIDTH, WINDOWHEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Resistor Match");
	glutDisplayFunc(DrawLoop);
	glutReshapeFunc(ResizeWindow);
	glutKeyboardFunc(KeyboardInput);
	glutMouseFunc(MouseInput);
	Inicializa();
	glutMainLoop();

	return 0;
}

void Inicializa(void)
{

	glClearColor(1, 1, 1, 0);
#if !_MSC_VER
	system("clear");
#endif
	printf("Press Q to quit...");

}


void DrawLoop()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 1);
	glBegin(GL_QUADS);
	{
		glVertex2i(0, 0);
		glVertex2i(50, 0);
		glVertex2i(50, 50);
		glVertex2i(0, 50);
	}
	glEnd();
	glFlush();
}

void ResizeWindow(GLsizei w, GLsizei h)
{

	if (h == 0)
		h = 1;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
		gluOrtho2D(0, WINDOWWIDTH, 0, WINDOWWIDTH * h / w);
	else
		gluOrtho2D(0, WINDOWHEIGHT * w / h, 0, WINDOWHEIGHT);

}

void KeyboardInput(unsigned char key, int x, int y)
{
	switch (key) {
	case 'Q':
	case 'q':
		exit(0);
		break;
	}

	glutPostRedisplay();
}
void MouseInput(int button, int state, int x, int y)
{
	printf("Button: %d\t", button);
	printf("x: %d\t", x);
	printf("y: %d\t", y);
	printf("state: %d\t", state);

	if (state == GLUT_DOWN)
	{
		printf("Pegou\t");
	}
	else if (state == GLUT_UP)
	{
		printf("Soltou\t");
	}
}