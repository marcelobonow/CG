
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

// OBS: Utilize k=1000 para testar o algoritmo.

void MyKeyboardFunc(unsigned char, int, int);
void Reload();

struct Transform {
	int pos1x;
	int pos1y;
	int pos2x;
	int pos2y;
	float ang1;
	float ang2;
	float k;
};
int yMax, xMax;
int totalElements = 0;
Transform transforms[500];

void curvaHermite(float k, float ang1, float ang4, int p1x, int p1y, int p4x, int p4y)

{
	int xmin, xmax, ymin, ymax;
	float max;

	if (p1x > p4x)
	{
		xmin = p4x;
		xmax = p1x;
	}
	else
	{
		xmin = p1x;
		xmax = p4x;
	}

	if (p1y > p4y)
	{
		ymin = p4y;
		ymax = p1y;
	}
	else
	{
		ymin = p1y;
		ymax = p4y;
	}

	if (xmax - xmin > ymax - ymin)
		max = xmax - xmin;
	else
		max = ymax - ymin;

	ang1 = (M_PI * ang1) / 180;
	ang4 = (M_PI * ang4) / 180;

	float r1x = k * cos(ang1);
	float r1y = k * sin(ang1);
	float r4x = k * cos(ang4);
	float r4y = k * sin(ang4);

	glColor3f(0, 0, 0);
	glLineWidth(3);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < max; i++)
	{
		float t = i / max;

		float xp1 = 2 * t * t * t - 3 * t * t + 1;
		float xp4 = -2 * t * t * t + 3 * t * t;

		float xr1 = t * t * t - 2 * t * t + t;
		float xr4 = t * t * t - t * t;

		float px = xp1 * p1x + xp4 * p4x + xr1 * r1x + xr4 * r4x;
		float py = xp1 * p1y + xp4 * p4y + xr1 * r1y + xr4 * r4y;

		glVertex2f(px, py);
	}
	glEnd();
	glFlush();

}

void Inicializa(void) {
	glClearColor(1, 1, 1, 1);
}

void Desenha(void) {

	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < totalElements; i++)
	{
		curvaHermite(transforms[i].k, transforms[i].ang1, transforms[i].ang2,
			transforms[i].pos1x, transforms[i].pos1y, transforms[i].pos2x, transforms[i].pos2y);
	}
	glutKeyboardFunc(MyKeyboardFunc);
	//curvaHermite(100, 35, 100, 100, 300, 200, 800);
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h) {
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		gluOrtho2D(0, xMax, 0, yMax * h / w);
	else
		gluOrtho2D(0, xMax * w / h, 0, yMax);
}

int main(int argc, char** argv) {
	Reload();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(xMax, yMax);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Simpsons");
	glutDisplayFunc(Desenha);
	glutReshapeFunc(AlteraTamanhoJanela);
	Inicializa();
	glutMainLoop();
	return 0;
}

void MyKeyboardFunc(unsigned char Key, int x, int y)
{
	switch (Key)
	{
	case 'r':
	{
		Reload();
		Desenha();
		break;
	}
	case 27:
	{
		exit(0);
		break;
	}
	};
}
void Reload()
{
	FILE* fileData;
	fileData = fopen("data.txt", "r");
	if (!fileData)
	{
		std::cout << "Error opening file";
		exit(1);
	}

	fscanf(fileData, "%d", &xMax);
	fscanf(fileData, "%d", &yMax);

	for (int i = 0; i < 500; i++)
	{
		transforms[i].pos1x = 0;
		transforms[i].pos1y = 0;
		transforms[i].pos2x = 0;
		transforms[i].pos2y = 0;
		transforms[i].ang1 = 0;
		transforms[i].ang2 = 0;
		transforms[i].k = 0;
	}
	int line;
	for (line = 0; !feof(fileData); line++)
	{
		fscanf(fileData, "%d", &transforms[line].pos1x);
		fscanf(fileData, "%d", &transforms[line].pos1y);
		fscanf(fileData, "%d", &transforms[line].pos2x);
		fscanf(fileData, "%d", &transforms[line].pos2y);
		fscanf(fileData, "%f", &transforms[line].ang1);
		fscanf(fileData, "%f", &transforms[line].ang2);
		fscanf(fileData, "%f", &transforms[line].k);
	}
	fclose(fileData);
	totalElements = line;
}
