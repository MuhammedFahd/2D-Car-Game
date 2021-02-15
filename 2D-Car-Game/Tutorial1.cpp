/*
Name: M.Fahd Fazal
UOW ID: w1789949
IIT ID: 2019656
youtube link: https://youtu.be/IwaqBk5sP_4
*/

#include "include\freeglut.h"	// OpenGL toolkit - in the local shared folder
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>  /* time */
#include <list>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <fstream>
#include <cstdlib>
#include <assert.h>
#include "Tutorial1.h"
using namespace std;

//set up some constants
#define X_CENTRE 0.0      /* centre point of border */
#define Y_CENTRE 0.0
#define LENGTH   85.0 /* lengths of sides of border */
# define NDEBUG 

GLfloat red = 1.0, green = 1.0, blue = 1.0;
GLfloat xmove = 0.0, ymove = 0.0, zmove = 0.0; //varibles to move the car
GLfloat angle = 0.0;   //variable angle to rotate the car 
GLfloat rotationDecider=0.0;   //rotation direction variable
string carDirection = "up";    //direction state of the car

//arrays to store the center cordinates of the square blocks 
vector<int> xCordinates;
vector<int> yCordinates;

//center cordinates of the car
float recCentreX = -((30.0 + 26.0) / 2);
float recCentreY = -((38.0 + 30.0) / 2);

//arrays to store the x cordinates and y cordinates of the car
vector<float> carX = {-30.0,-26.0};
vector<float> carY ={-38.0,-30.0};
int score = 50;
unsigned char pressedKey;
bool* keyStates = new bool[256];

//method to display string in the screen
void writeBitmapString(void* font, char* string)
{
	char* c;
	for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

/* reshape callback function
executed when window is moved or resized */
void reshape(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, width, height);
	glLoadIdentity();
	/* uses orthographic (parallel) projection
	use xmin = -1, xmax = 1
	ymin = -1, ymax = 1
	znear = -1, zfar = 1 - not relevant here (2D) */
	glOrtho(-50.0, 50.0, -50.0, 50.0, -50.0, 50.0);
	glMatrixMode(GL_MODELVIEW);
}

//method to restart the game when it is over 
void restartGame() {
	//all varibles are set to their initial values
	xmove = 0.0;
	ymove = 0.0;
	zmove = 0.0;
	angle = 0.0;
	rotationDecider = 0.0;
	carDirection = "up";
	xCordinates.clear();
	yCordinates.clear();
	carX = { -30.0,-26.0 };
	carY = { -38.0,-30.0 };
	score = 50;
	glutPostRedisplay();  //to run the display function again 
}

//method to display the score 
void displayScore() {
	glColor3f(1.0, 0.0, 0.0);
	glRasterPos2f(-40.0,45.0);
	writeBitmapString(GLUT_BITMAP_HELVETICA_18, "Score:");

	int addValue = score / 10;
	//score has been displayed using ASCII values 
	glRasterPos2f(-28.0, 45.0);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,(char)48+addValue);
	glRasterPos2f(-26.0, 45.0);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (char)48);
}

//method to check the collision between the car and the square blocks
void checkCollision(float x,float y) {

	//variables to store the xmin and ymin of the square blocks 
	int squareX;
	int squareY;
	
	//loop through all the square blocks and checks whether there is a collision 
	for (int i = 0; i < 5; i++) {
		squareX = xCordinates[i] - 8 / 2;
		squareY = yCordinates[i] - 8 / 2;
		if ((x>=squareX && x<=(squareX+8)) || ((x+4.0)>=squareX && (x+4.0)<=(squareX+8))) {
			if ((y>=squareY && y<=(squareY+8)) || ((y+8.0)>=squareY && (y+8.0)<=(squareY+8))) {
				cout << "collided\n";
				score = score - 10; // score is reduced by 10 if there is a collision 
			}
		}
	}
	//if score is 0 the game will be restarted 
	if (score == 0) {
		cout << "game over\n";
		restartGame(); //method is called to restart the game 
	}
	

}

//method to check whether the car has reached the finish line 
void gameEnd(float x,float y) {

	//variables to store xmin and ymin of the finish line box
	float endPointX1 = 20.0;
	float endPointY1 = 39.5;
	if ((x >= endPointX1 && x <= (endPointX1 + 15.0)) || ((x + 4.0) >= endPointX1 && (x + 4.0) <= (endPointX1 + 15.0))) {
		if ((y >= endPointY1 && y <= (endPointY1 + 3.0)) || ((y + 8.0) >= endPointY1 && (y + 8.0) <= (endPointY1 + 3.0))) {
			cout << "game over\n";
			restartGame(); //method is called to restart the game when collision is detected 
		}
	}
}

//method to check the hold key
void myKeyboardUpFunction(unsigned char key, int x, int y) {
	pressedKey = key;
	keyStates[key] = false;
}

//method to perform keyboard functions 
void myKeyboardFunction(unsigned char key, int x, int y) {
	//variables to store current x and y cordinates of the car
	float y1;
	float y2;
	float x1;
	float x2;

	//variables to store the key pressed 
	pressedKey = key;
	keyStates[key] = true;

	//when w is pressed checks the current direction of the car and rotate it towards up and move it accordingly
	if (keyStates['w'] == true || keyStates['W'] == true) {
		if (carDirection == "right") {
			carDirection = "up";
			angle =angle+270.0;
			rotationDecider = -1.0;
		}
		else if (carDirection == "down") {
			carDirection = "up";
			angle = angle + 180.0;
			rotationDecider = -1.0;
		}
		else if (carDirection == "left") {
			carDirection = "up";
			angle = angle + 90.0;
			rotationDecider = -1.0;
		}
		else {
			ymove = ymove + 1.0;
			//increasing the y values by one unit when the car is moved up by one unit 
			y1 = carY[0] + 1.0;
			y2 = carY[1] + 1.0;
			x1 = carX[0];
			x2 = carX[1];

			//clearing the arrays and storing the new x and y values of the car
			carX.clear();
			carY.clear();
			carY.push_back(y1);
			carY.push_back(y2);
			carX.push_back(x1);
			carX.push_back(x2);

			checkCollision(min(x1, x2), min(y1, y2));	//calls the method to check for collision by passing min x and y values of the car
			gameEnd(min(x1, x2), min(y1, y2)); //calls the method to check for finish line collision by passing min x and y values of the car
		}
		glutPostRedisplay();
	}
	//when s is pressed checks the current direction of the car and rotate it towards down and move it accordingly
	else if (keyStates['s'] == true || keyStates['S'] == true) {
		if (carDirection == "up") {
			carDirection = "down";
			angle = angle+180.0;
			rotationDecider = -1.0;

		}
		else if (carDirection == "right") {
			carDirection = "down";
			angle = angle + 90.0;
			rotationDecider = -1.0;
		}
		else if (carDirection == "left") {
			carDirection = "down";
			angle = angle+270;
			rotationDecider = -1.0;
		}
		else {
			ymove = ymove - 1.0;
			//decreasing the y values by one unit when the car is moved down by one unit 
			y1 = carY[0] - 1.0;
			y2 = carY[1] - 1.0;
			x1 = carX[0];
			x2 = carX[1];

			//clearing the arrays and storing the new x and y values of the car
			carX.clear();
			carY.clear();
			carY.push_back(y1);
			carY.push_back(y2);
			carX.push_back(x1);
			carX.push_back(x2);
			checkCollision(min(x1, x2), min(y1, y2));  //calls the method to check for collision by passing min x and y values of the car
			gameEnd(min(x1, x2), min(y1, y2));  //calls the method to check for finish line collision by passing min x and y values of the car
		}
		glutPostRedisplay();
	}
	//when d is pressed checks the current direction of the car and rotate it towards right and move it accordingly
	else if (keyStates['d']==true || keyStates['D'] == true) {
		if (carDirection == "up") {
			carDirection = "right";
			angle = angle + 90.0;
			rotationDecider = -1.0;
		}
		else if (carDirection == "down") {
			carDirection = "right";
			angle = angle+270;
			rotationDecider = -1.0;
		}
		else if (carDirection == "left") {
			carDirection = "right";
			angle = angle + 180.0;
			rotationDecider = -1.0;
		}
		else {
			xmove = xmove + 1.0;
			//increasing the x values by one unit when the car is moved right by one unit 
			y1 = carY[0];
			y2 = carY[1];
			x1 = carX[0] + 1.0;
			x2 = carX[1] + 1.0;

			//clearing the arrays and storing the new x and y values of the car
			carX.clear();
			carY.clear();
			carY.push_back(y1);
			carY.push_back(y2);
			carX.push_back(x1);
			carX.push_back(x2);
			checkCollision(max(x1, x2), min(y1, y2));
			gameEnd(max(x1, x2), min(y1, y2));
		}
		glutPostRedisplay();
	}
	//when a is pressed checks the current direction of the car and rotate it towards left and move it accordingly
	else if (keyStates['a'] == true || keyStates['A'] == true) {
		if (carDirection == "up") {
			carDirection = "left";
			angle = angle + 270.0;
			rotationDecider = -1.0;
		}
		else if (carDirection == "right") {
			carDirection = "left";
			angle = angle + 180.0;
			rotationDecider = -1.0;
		}
		else if (carDirection == "down") {
			carDirection = "left";
			angle = angle + 90.0;
			rotationDecider = -1.0;
		}
		else {
			xmove = xmove - 1.0;
			//decreasing the x values by one unit when the car is moved left by one unit 
			y1 = carY[0];
			y2 = carY[1];
			x1 = carX[0] - 1.0;
			x2 = carX[1] - 1.0;

			//clearing the arrays and storing the new x and y values of the car
			carX.clear();
			carY.clear();
			carY.push_back(y1);
			carY.push_back(y2);
			carX.push_back(x1);
			carX.push_back(x2);
			checkCollision(min(x1, x2), min(y1, y2));
			gameEnd(min(x1, x2), min(y1, y2));
		}
		glutPostRedisplay();
	}

	//when r and d is pressed together the car rotates in the clockwise direction about the center of the car
	if (keyStates['r']==true && keyStates['d']==true) {
		rotationDecider = -1.0;
		angle = angle + 5.0;
		xmove = xmove-1.0;
		y1 = carY[0];
		y2 = carY[1];
		x1 = carX[0] - 1.0;
		x2 = carX[1] - 1.0;
		carX.clear();
		carY.clear();
		carY.push_back(y1);
		carY.push_back(y2);
		carX.push_back(x1);
		carX.push_back(x2);
		glutPostRedisplay();
	}

	//when r and a is pressed together the car rotates in the anticlockwise direction about the center of the car
	if (keyStates['r'] == true && keyStates['a'] == true) {
		rotationDecider = 1.0;
		angle = angle + 5.0;
		xmove = xmove + 1.0;
		y1 = carY[0];
		y2 = carY[1];
		x1 = carX[0] + 1.0;
		x2 = carX[1] + 1.0;
		carX.clear();
		carY.clear();
		carY.push_back(y1);
		carY.push_back(y2);
		carX.push_back(x1);
		carX.push_back(x2);
		glutPostRedisplay();
	}
	

}

//method for the popup menu to switch betwwen light mode and dark mode 
void popUpMenu(GLint id)
{
	if (id == 1)
	{
		red = 0.0;
		green = 0.0;
		blue = 0.0;
		glClearColor(1.0, 1.0, 1.0, 1.0);
	}
	else
	{
		red = 1.0;
		green = 1.0;
		blue = 1.0;
		glClearColor(0.0, 0.0, 0.0, 0.0);
	}
	glutPostRedisplay();
}

//method to generate a random number between a given range
//this code is taken from stackoverflow (reference)
int randomNumber(int min, int max) //range : [min, max]
{
	static bool first = true;
	if (first)
	{
		srand(time(NULL)); //seeding for the first time only!
		first = false;
	}
	return min + rand() % ((max + 1) - min);
}



//method to check the range of the generated random number 
bool checkRange(int squareNumber,int randomNum, vector<int> checkArray) {
	bool result = false;
	if (squareNumber != 0) {
		//it checks whether the generated random number is in the range of any square blocks 
		//this is done to avoid overlap of the blocks 
		for (int i = 0; i < checkArray.size(); i++) {
			if (randomNum > (checkArray[i] - 8) && randomNum < (checkArray[i] + 8) && i!=squareNumber) {
				result = true;
			}
		}
	}
	return result;
}

//method to draw the square block 
void drawSquare(int squareNumber) {
	//generate the center cordinates of the square and store it in the variables
	int x1= randomNumber(-30,30);
	int y1 = randomNumber(-30,30);

	int length = 8; //length of the square 
	
	//loop will run until random numbers are generated outside of the ranges of the square that are already created 
	while (checkRange(squareNumber, x1, xCordinates) || checkRange(squareNumber, y1, yCordinates)) {
		if (checkRange(squareNumber, x1, xCordinates)) {
			x1 = randomNumber(-30, 30);
		}
		if (checkRange(squareNumber, y1, yCordinates)) {
			y1 = randomNumber(-30, 30);
		}
	}

	//checks whether square blocks has been already created if so x values will be taken from the arrays 
	//otherwise newly generated random number will be assigned 
	if (xCordinates.size()<5 ) {
		xCordinates.push_back(x1);
	}
	else {
		switch (squareNumber) {
		case 0:
			x1 = xCordinates[0];
			break;
		case 1:
			x1 = xCordinates[1];
			break;
		case 2:
			x1 = xCordinates[2];
			break;
		case 3:
			x1 = xCordinates[3];
			break;
		case 4:
			x1 = xCordinates[4];
			break;
		}
	}

	//checks whether square blocks has been already created if so y values will be taken from the arrays 
	//otherwise newly generated random number will be assigned 
	if (yCordinates.size() < 5) {
		yCordinates.push_back(y1);
	}
	else {
		switch (squareNumber) {
		case 0:
			y1 = yCordinates[0];
			break;
		case 1:
			y1 = yCordinates[1];
			break;
		case 2:
			y1 = yCordinates[2];
			break;
		case 3:
			y1 = yCordinates[3];
			break;
		case 4:
			y1 = yCordinates[4];
			break;
		}
	}

	//code to create the square after x and y values have been assigned
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POLYGON);

	//specify the vertices (points in 3D space) of the shape - note that these are 2D points
	glVertex2f(x1 - length / 2, y1 - length / 2);
	glVertex2f(x1 - length / 2, y1 + length / 2);
	glVertex2f(x1 + length / 2, y1 + length / 2);
	glVertex2f(x1 + length / 2, y1 - length / 2);

	glEnd();
	

}

//method to draw the car,rotate and translate 
void car() {

	glColor3f(0.0, 0.0, 1.0);
	glPushMatrix();
	glTranslatef(xmove, ymove, zmove);
	glTranslatef(recCentreX, recCentreY, 0.0);    //translate back to initial position
	glRotatef(angle, 0.0, 0.0,rotationDecider);   //rotate about the center of the car
	glTranslatef(-recCentreX,-recCentreY,0.0);   //translate to the origin 

	//body of the car
	glRectf(-30.0,-38.0,-26.0,-30.0);

	//spoiler of the car
	glColor3f(0.0, 1.0, 0.0);
	glRectf(-32.0, -38.0, -24.0, -37.0);

	//right side wheel of the car
	glColor3f(0.0, 1.0, 0.0);
	glRectf(-26.0, -34.0, -25.0, -31.0);

	//left side wheel of the car
	glColor3f(0.0, 1.0, 0.0);
	glRectf(-31.0, -34.0, -30.0, -31.0);

	glPopMatrix();
	
}



/* display callback function
called whenever contents of window need to be re-displayed */
//this is the all important drawing method - all drawing code goes in here
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);   /* clear window */
	glColor3f(red, green, blue);        /* white drawing objects */

   
    //drawing the border
	glBegin(GL_LINE_LOOP);

	//specify the vertices (points in 3D space) of the shape - note that these are 2D points
	glVertex2f(X_CENTRE - LENGTH / 2, Y_CENTRE - LENGTH / 2);
	glVertex2f(X_CENTRE - LENGTH / 2, Y_CENTRE + LENGTH / 2);
	glVertex2f(X_CENTRE + LENGTH / 2, Y_CENTRE + LENGTH / 2);
	glVertex2f(X_CENTRE + LENGTH / 2, Y_CENTRE - LENGTH / 2);


	glEnd();

	
	car();	//car method is called to draw the car

	//calling the drawsquare method five to draw 5 square blocks
	drawSquare(0);
	drawSquare(1);
	drawSquare(2);
	drawSquare(3);
	drawSquare(4);

	//finish line
	glColor3f(0.0,1.0,0.0);
	glRectf(20.0,39.5,35.0,42.5);

	//starting line
	glColor3f(1.0, 0.0, 0.0);
	glRectf(-20.0, -39.5, -35.0, -42.5);

	displayScore();  //calling the displayscore method to display the current score in the screen 



	glFlush();     /* execute drawing commands in buffer */
}

/* graphics initialisation */
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);   /* window will be cleared to black */
}

//rename this to main(...) and change example 2 to run this main function
int main(int argc, char** argv)
{
	/* window management code ... */
	/* initialises GLUT and processes any command line arguments */
	glutInit(&argc, argv);
	/* use single-buffered window and RGBA colour model */
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	/* window width = 400 pixels, height = 400 pixels */
	glutInitWindowSize(500, 500);
	/* window upper left corner at (100, 100) */
	glutInitWindowPosition(100, 100);
	/* creates an OpenGL window with command argument in its title bar */
	glutCreateWindow("Coursework 1");
	glutKeyboardFunc(myKeyboardFunction);
	glutKeyboardUpFunc(myKeyboardUpFunction);

	glutCreateMenu(popUpMenu);
	glutAddMenuEntry("Light mode", 1);
	glutAddMenuEntry("Dark mode", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop();
	return 0;
}

