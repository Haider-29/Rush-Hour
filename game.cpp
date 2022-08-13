//============================================================================
// Name        : game.cpp
// Author      : Fatima Saad
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Rush Hour...
//============================================================================

#ifndef RushHour_CPP_
#define RushHour_CPP_
#include "util.h"
#include <iostream>
#include<string>
#include <ctime>
#include <cstdlib>
#include<cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;

void score();//function to store score
void readName(); //function to record names
void Leaderboard(); //function to create leaderboard
void RandomCar(); //function to generate a random car
void screenDisplay(); //function to display screen
void taxiPosition(); //function to display car on top left
void desiredDestination(); //function to generate desired destination
void pointsIncrease();//function to increase points
void pointsDecrease();//function to decrease points
void CarColour(); //function to change car colour
void CarSpeed(); //function to increase taxi speed
void timeEndGame(); //function to calculate 3 min



string board[20][20];

// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}

	

int xI = 1000, yI = 1000;
                          
void drawCar() {

	DrawSquare(500, 500, 50, colors[RED]);

	board[7][2] = "car";
	board[12][8] = "car";
	board[10][14] = "car";
	board[8][18] = "car";
	board[7][2] = "car";

	
	for(int i = 0; i <= 20; i++){
		for(int j = 0; j<=20; j++){ 
			if(board[i][j] == "car"){
				DrawSquare( (i*50)+5 ,(j*50) +10,20,colors[MIDNIGHT_BLUE]);	
				DrawCircle( (i*50)+7 ,(j*50) +9,5,colors[BLACK]);
				DrawCircle( (i*50)+22,(j*50) +9,5,colors[BLACK]);
				DrawSquare( (i*50)+8 ,(j*50) +20, 7 ,colors[LIGHT_GOLDEN_ROD_YELLOW]);
				DrawSquare( (i*50)+16,(j*50) +20, 7 ,colors[LIGHT_GOLDEN_ROD_YELLOW]);	
			
			}
		}
	}

	
	glutPostRedisplay();

}





bool flag = true; 
void moveCar() {
	
	if (xI > 10 && flag) {
		xI -= 50;
		cout << "going left";
		if(xI < 100)
			
			flag = false;

	}
	else if (xI < 1000 && !flag) {
		cout << "go right";
		xI += 10;
		if (xI > 900)
			flag = true;
	}
}




/*
 * Main Canvas drawing function.
 * */


void GameDisplay()/**/{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(255/*Red Component*/, 255,	//148.0/255/*Green Component*/,
			255/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	
	
	
	for(int i = 0; i <= 20; i++){
		for(int j = 0; j<=20; j++){
		
			if(board[i][j] == "human"){
				DrawCircle((i*50)+25 ,(j*50)-10,5,colors[BLACK]);
				DrawLine((i*50)+25,(j*50)-10,(i*50)+25,(j*50)-30,3,colors[BLACK]);
			    DrawLine((i*50)+19,(j*50)-18,(i*50)+30,(j*50)-18,3,colors[BLACK]);        
				DrawLine((i*50)+20,(j*50)-35,(i*50)+25,(j*50)-27,3,colors[BLACK]); 
				DrawLine((i*50)+25,(j*50)-27,(i*50)+30,(j*50)-35,3,colors[BLACK]);
				
			}
			
			
			if(board[i][j] == "build"){
				DrawSquare( i*50 , j*50 ,50,colors[BLACK]);
				
			}

			if (board[i][j] == "tree")
			{
				DrawCircle((i*50)+25 ,(j*50) -20,10,colors[FOREST_GREEN]);
				DrawLine((i*50)+25,(j*50)-20,(i*50)+25,(j*50)-43, 6 ,colors[BROWN]);
			}
			
			DrawLine(i*50 , (j*50) , i*50, (j*50)-50 ,1 , colors[BLACKO]);
			DrawLine(i*50 + 50 , (j*50) , i*50, (j*50) ,1 , colors[BLACKO]);
			
		}


	}
	
	drawCar();
	
	
	glutSwapBuffers(); // do not modify this line..

}



/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
	if (key
			== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...
		xI -= 10;

	} else if (key
			== GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
		xI += 10;
	} else if (key
			== GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {
		yI += 10;
	}

	else if (key
			== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {
		yI -= 10;
	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}

	if (key == 'b' || key == 'B') //Key for placing the bomb
			{
		//do something if b is pressed
		cout << "b pressed" << endl;

	}
	glutPostRedisplay();
}



/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {

	// implement your functionality here
	moveCar();

	// once again we tell the library to call our Timer function after next 1000/FPS
	
	glutTimerFunc(1, Timer, 0);
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
	cout << x << " " << y << endl;
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {
	//cout << x << " " << y << endl;
	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
			{
		cout << GLUT_DOWN << " " << GLUT_UP << endl;

	} else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{
			cout<<"Right Button Pressed"<<endl;

	}
	glutPostRedisplay();
}
/*
 * our gateway main function
 * */




int main(int argc, char*argv[]) {

	for (int i = 0; i < 20 ; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			board[i][j]="initialValue";
		}
	}

	board[11][2] = "tree";
	board[5][7] = "tree";
	board[12][11] = "tree";
	board[5][14] = "tree";
	board[15][17] = "tree";
	board[9][13] = "tree";
	board[15][17] = "tree";
	board[10][5] = "tree";
	board[14][14] = "tree";
	board[12][17] = "tree";

	
	board[3][3] = "build";
	board[4][3] = "build";
	
	board[8][4] = "build";
	board[9][4] = "build";
	board[9][5] = "build";
	
	board[17][3] = "build";
	board[17][2] = "build";
	board[16][2] = "build";
	board[15][2] = "build";
	
	board[2][8] = "build";
	board[3][8] = "build";
	board[3][9] = "build";
	
	board[15][8] = "build";
	board[15][7] = "build";
	board[16][7] = "build";
	
	board[6][14] = "build";
	board[7][14] = "build";
	board[8][14] = "build";
	board[8][15] = "build";
	board[8][16] = "build";
	
	board[16][12] = "build";
	board[15][12] = "build";
	board[14][12] = "build";
	board[13][12] = "build";
	board[13][13] = "build";
	board[13][14] = "build";
	
	board[18][15] = "build";
	board[18][16] = "build";
	board[17][16] = "build";
	board[17][17] = "build";
	
	board[3][17] = "build";
	board[3][18] = "build";
	board[2][18] = "build";
	
	srand (time(0));
	 	int xCoord1, yCoord1;
	 	do{xCoord1 = rand()%20;
	 	 yCoord1 = rand()%20;
 		board[xCoord1][yCoord1]="human";
		cout << "human" << endl;
		}while (board[xCoord1][yCoord1]=="build" || board[xCoord1][yCoord1]=="car" || board[xCoord1][yCoord1]=="tree");

		int xCoord2, yCoord2;
	 	do{xCoord2 = rand()%20;
	 	 yCoord2 = rand()%20;
 		board[xCoord2][yCoord2]="human";
		cout << "human" << endl;
		}while (board[xCoord2][yCoord2]=="build" || board[xCoord2][yCoord2]=="car" || board[xCoord2][yCoord2]=="tree");
	
		int xCoord3, yCoord3;
	 	do{xCoord3 = rand()%20;
	 	 yCoord3 = rand()%20;
 		board[xCoord3][yCoord3]="human";
		cout << "human" << endl;
		}while (board[xCoord3][yCoord3]=="build" || board[xCoord3][yCoord3]=="car" || board[xCoord3][yCoord3]=="tree");

		int xCoord4, yCoord4;
	 	do{xCoord4 = rand()%20;
	 	 yCoord4 = rand()%20;
 		board[xCoord4][yCoord4]="human";
		cout << "human" << endl;
		}while (board[xCoord4][yCoord4]=="build" || board[xCoord4][yCoord4]=="car" || board[xCoord4][yCoord4]=="tree");

		int xCoord5, yCoord5;
	 	do{xCoord5 = rand()%20;
	 	 yCoord5 = rand()%20;
 		board[xCoord5][yCoord5]="human";
		cout << "human" << endl;
		}while (board[xCoord5][yCoord5]=="build" || board[xCoord5][yCoord5]=="car" || board[xCoord5][yCoord5]=="tree");
	
	int width = 1000, height = 1000; // i have set my window size to be 1000 x 1000

	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50 , 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("Rush Hour by Fatima Saad"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* RushHour_CPP_ */
