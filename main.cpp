#ifdef _WIN32
	#define NOMINMAX	
	#include"GL/freeglut.h"	// Windows machines: freeGLUT 3 is provided here, make sure you have x64 set as architecture
#else
	#include<GLUT/glut.h> // MacOS: comes with GLUT pre-installed
#endif
// Selman Tabet (@selmantabet - https://selman.io/) - OpenGL Rainbow Cube Render (HBKU DataVis Course Assignment)
// Press the up arrow key to increase point size and the down arrow key to decrease it.
#include<iostream>

// TODO: part of Assignment 1F goes here
#include "timer.h"
float alpha = 0.0f;
float size = 1.0f;
timer T;

// TODO: part of Assignment 1G goes here
#include<vector>
std::vector<float> positions;
std::vector<float> colors;

// TODO: part of Assignment 1G goes here

int winwidth = 512;		// initial window width
int winheight = 512;	// initial window height

void display(void) {
	// This function will be called to generate a new frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			// Clear both color buffer and depth buffer
	
	// TODO: part of Assignment 1D goes here.
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -3.0f);
	glRotatef(alpha, 0.0f, 1.0f, 0.0f); //Rotate along y axis
	//glBegin(GL_TRIANGLES);
	glBegin(GL_POINTS);

	// TODO: Assignment 1E goes here.
	//glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
	//glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 0.0);
	//glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 1.0f, 0.0f);
	//glEnd();

	for (int n = 0; n < positions.size(); n += 3) {
		glColor3fv(&colors[n]); //Point color
		glVertex3fv(&positions[n]); //Point location
	}

	// TODO: part of Assignment 1F goes here
	alpha = T.query() * 60; // 60 degree rotation per second

	// TODO: part of Assignment 1G goes here
	glEnd();
	glutSwapBuffers();											// Show rendered image
}

void keyboard(unsigned char key, int x, int y) {
	// key will contain the key that was pressed
	// x,y are the mouse coordinates when the key was pressed.	
	
	// TODO: Assignment 1B goes here.	
	if (key == 27) exit(0);

}

void special_key(int key, int x, int y) {
	// key will contain a code (e.g., GLUT_KEY_F1, GLUT_KEY_LEFT, ...)
	// See https://www.opengl.org/resources/libraries/glut/spec3/node54.html
	// x,y are the mouse coordinates when the key was pressed.

	// TODO: Assignment 1C goes here
	if (key == GLUT_KEY_F1) {
		printf("------------ Help ------------\n");
		printf("The following are the available mouse and key inputs for this program:\n\n");
		printf("-- Esc: Close the program.\n");
		printf("-- UP Arrow Key: Increase the point size.\n");
		printf("-- DOWN Arrow Key: Decrease the point size.\n");
		printf("-- F1: Well, you got here somehow, so.... :)\n");
		printf("-- F2: Show GPU diagnostic data.\n");
		printf("\n");
	}
	// TODO: part of Assignment 1G goes here

	if (key == GLUT_KEY_UP) {
		size += 0.3f;
		glPointSize(size);
	}

	if (key == GLUT_KEY_DOWN) {
		size -= 0.3f;
		glPointSize(size);
	}

	// TODO: Bonus points can be obtained here
	if (key == GLUT_KEY_F2) {
		const unsigned char* vnd = glGetString(GL_VENDOR);
		std::cout << vnd << std::endl;
		const unsigned char* rnd = glGetString(GL_RENDERER);
		std::cout << rnd << std::endl;
		const unsigned char* ver = glGetString(GL_VERSION);
		std::cout << ver << std::endl;
		printf("\n");
	}
}

void mouse_button(int button, int state, int x, int y) {
	// button can be GLUT_LEFT_BUTTON, GLUT_RIGHT_BUTTON, GLUT_MIDDLE_BUTTON
	// state can be GLUT_UP or GLUT_DOWN
	// x,y is the mouse coordinate
}

void mouse_motion(int x, int y) {
	// This function is called when the mouse is moved and a button is pressed
	// x,y are the mouse coordinates
}

void mouse_passive_motion(int x, int y) {
	// This function is called when the mouse is moved and no button is pressed
	// x,y are the mouse coordinates
}

void reshape(int width, int height) {
	// This function is called when the window is resized
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// TODO: Part of assignment 1D goes here
	GLdouble FOV = 90;
	GLdouble asp = double(width) / double(height); //Square 1:1
	GLdouble zn = 0.01;
	GLdouble zf = 100;
	gluPerspective(FOV, asp, zn, zf);
	glMatrixMode(GL_MODELVIEW);
}

void init(void) {
	// Here, we set up our data structures and OpenGL state
	// As an example, we can set the background color:
	//glEnable(GL_DEPTH_TEST);
	//glClearColor(0.2f, 0.2f, 1.0f, 1.0f);

	// TODO: Assignment 1A goes here
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);
	glClearColor(0.5f, 0.5f, 0.5f, 0.5f);

	// TODO: part of Assignment 1F goes here
	printf("Time since last reset (in seconds): ");
	T.reset();
	std::cout << T.query() << std::endl;

	// TODO: part of Assignment 1G goes here
	float x, y, z; //Position floats
	float Cx, Cy, Cz; //Color floats
	for (int i = 0; i < 32; i++) {
		x = 2.0f * float(i) / 31.0f - 1.0f;
		for (int j = 0; j < 32; j++) {
			y = 2.0f * float(j) / 31.0f - 1.0f;
			for (int k = 0; k < 32; k++) {
				z = 2.0f * float(k) / 31.0f - 1.0f;

				Cx = (x + 1.0f) / 2.0f; //Since x, y and z range from -1 to 1, normalize to 0-1
				Cy = (y + 1.0f) / 2.0f;
				Cz = (z + 1.0f) / 2.0f;

				positions.push_back(x);
				colors.push_back(Cx);
				positions.push_back(y);
				colors.push_back(Cy);
				positions.push_back(z);
				colors.push_back(Cz);
			}
		}
	}
	

	// Make triangle centered on MacOS:
	// The problem is that reshape() should be called initially,
	// but somehow that does not seem to happen. Let's call it
	// manually here and hope it works...
	reshape(winwidth, winheight);
	// If it does not work, the triangle will center once
	// you resize the window.
}

void cleanup(void) {
	// Here, you can clean up data structures
}

int main(int argc, char** argv) {
	atexit(cleanup);											// This makes sure that you call cleanup() before exiting
	std::cout << "CPEG 418 Assignment 1" << std::endl;
	glutInit(&argc, argv);										// Initialize GLUT
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);	// Specify display parameters: double RGBA-color buffer plus depth buffer
	glutInitWindowSize(winwidth, winheight);					// Set up the initial window size
	glutCreateWindow("Assignment 1");							// Create a window with title "Assignment 1"
	glutDisplayFunc(display);									// The display() function is called for each new frame
	glutIdleFunc(glutPostRedisplay);							// Keep on rendering frames
	glutKeyboardFunc(keyboard);									// The keyboard() function is called when a key is pressed
	glutSpecialFunc(special_key);								// Called when a special key (F1, LEFT, RIGHT, etc.) is pushed
	glutMouseFunc(mouse_button);								// The mouse_button() function is called when the user clicks or releases a button
	glutMotionFunc(mouse_motion);								// The mouse_motion() function is called when the mouse moves while a button is pressed
	glutPassiveMotionFunc(mouse_passive_motion);				// The mouse_passive_motion() function is called then the mouse moves without a button begin pressed.
	glutReshapeFunc(reshape);									// The reshape() function is called when the window is resized
	init();														// This function initializes a few OpenGL things
	glutShowWindow();											// Show the window
	glutMainLoop();												// enter the main loop
	return 0;
}