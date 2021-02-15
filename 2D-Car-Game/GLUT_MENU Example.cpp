/*
* 5CCGD003W - Tutorial 1 - example solution code
* program draws a white rectangle on a black background
*/
// Code modified by Dr Anastassia Angelopoulou 
// Original code by Dr Phil Trwoga

#include "include\freeglut.h"	// OpenGL toolkit - in the local shared folder
#include <cmath>
#include <iostream>

//set up some constants
#define X_CENTRE 0.0      /* centre point of square */
#define Y_CENTRE 0.0
#define LENGTH   1.0      /* lengths of sides of square */


//forward declaration - best in the header
void drawStar(GLfloat radius, GLfloat x, GLfloat y);
void drawSquare(GLfloat length, GLfloat x, GLfloat y);
void myFirstmenu(GLint id);

/* reshape callback function
   executed when window is moved or resized. This function should be used in Tutorial 1 */
void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();
	/* uses orthographic (parallel) projection
	   use xmin = -1, xmax = 1
		   ymin = -1, ymax = 1
		   znear = -1, zfar = 1 - not relevant here (2D)*/
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);   //sets the x,y,z plane from -1 to 1

	glMatrixMode(GL_MODELVIEW);
}


/* display callback function
   called whenever contents of window need to be re-displayed */
   //this is the all important drawing method - all drawing code goes in here
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);     /* clear window */
	/*glColor3f(1.0, 1.0, 1.0);        /* white drawing objects */
	glColor3f(0.0, 1.0, 1.0);          /* blue drawing objects */
	/* define object to be drawn as a square polygon */

 //blue rectangle on a red background
 glBegin(GL_POLYGON);
	   glVertex2f( X_CENTRE - LENGTH / 2, Y_CENTRE - LENGTH / 2);
	   glVertex2f( X_CENTRE - LENGTH / 2, Y_CENTRE + LENGTH / 2);
	   glVertex2f( X_CENTRE + LENGTH / 2, Y_CENTRE + LENGTH / 2);
	   glVertex2f( X_CENTRE + LENGTH / 2, Y_CENTRE - LENGTH / 2);
 glEnd();

	glFlush();     /* execute drawing commands in buffer */
}


/* graphics initialisation */
void init(void)
{
	/*glClearColor (0.0, 0.0, 0.0, 0.0);   /* window will be cleared to black */
	glClearColor(1.0, 0.0, 0.0, 0.0);     /* window will be cleared to red */
}


void myFirstmenu(GLint id)
{
	if (id == 1)
	{
		glClearColor(0.0, 0.0, 0.9, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	else
	{
		glClearColor(0.0, 0.9, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	glutPostRedisplay();
}
//rename this to main(...) and change example 2 to run this main function
int main(int argc, char** argv)
{
	/* window management code ... */
/* initialises GLUT and processes any command line arguments */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	/* window width = 400 pixels, height = 400 pixels */
	/* window width = 640 pixels, height = 480 pixels for a 4:3 ascpect ratio */
	/* window width = 1024 pixels, height = 576 pixels for a 16:9 ascpect ratio */
	glutInitWindowSize(400, 400);
	/* window upper left corner at (100, 100) */
	glutInitWindowPosition(100, 100);
	/* creates an OpenGL window with command argument in its title bar */
	glutCreateWindow("Example 1");

	glutCreateMenu(myFirstmenu);
	glutAddMenuEntry("Blue", 1);
	glutAddMenuEntry("Green", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);


	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}

