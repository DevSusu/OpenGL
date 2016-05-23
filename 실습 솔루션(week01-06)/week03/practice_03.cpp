//implement here - include header files 
#include "triangle.h"
#include <GL/glut.h>

float** position; //data to save vertices position.

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < 3; i++)
		glVertex3f(position[i][0], position[i][1], position[i][2]);
	glEnd();

	glutSwapBuffers();
}

void main(int argc, char **argv) {
	//implement here - position is 3x3 array, allocate the memory.
	position = new float*[3];
	for(int i = 0; i < 3; i++)
		position[i] = new float[3];
	readFile(position);
	
	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("practice_03!");

	// register callbacks
	glutDisplayFunc(renderScene);

	// enter GLUT event processing cycle
	glutMainLoop();

	for(int i=0;i <3; i++){
		delete position[i];
	}
	delete position;
}
