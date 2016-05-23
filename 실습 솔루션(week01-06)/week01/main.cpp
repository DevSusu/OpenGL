#include <GL/glut.h>
#include <math.h>

#define PI 3.141592

void renderScene(void) {
	float radius = 0.5;
	float center_x = 0, center_y = 0, center_z = 0;
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float step = 10;

	glColor3f(1,0,0);
	
	glBegin(GL_TRIANGLE_FAN);
		glVertex3d(center_x, center_y, center_z);
		for(int i=0; i<step+1; i++){
			float x=radius*cos(2.0*PI/step*i);
			float y=radius*sin(2.0*PI/step*i);
			glVertex3d(x,y,center_z);
		}
	glEnd();

	glutSwapBuffers();
}

void main(int argc, char **argv) {
	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(500,500);
	glutCreateWindow("Practice 01");

	// register callbacks
	glutDisplayFunc(renderScene);

	// enter GLUT event processing cycle
	glutMainLoop();
}
