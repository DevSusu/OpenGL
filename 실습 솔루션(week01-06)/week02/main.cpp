#include "ReadFile.h"
#include <GL/glut.h>
#include <math.h>

#define PI 3.141592

float cen_x, cen_y, cen_z;
float radius;

void drawCircle(float center_x, float center_y, float center_z, float radius){
	static int count = 0;
	float step = 100;
	if(count % 2 == 0)
		glColor3f(1,0,0);
	else
		glColor3f(1,1,1);
	glBegin(GL_TRIANGLE_FAN);
		glVertex3d(center_x, center_y, center_z);
		for(int i=0; i<step+1; i++){
			float x=radius*cos(2.0*PI/step*i);
			float y=radius*sin(2.0*PI/step*i);
			glVertex3d(x,y,center_z);
		}
	glEnd();
	count++;
	if(radius > 0.0){
		
		drawCircle(center_x, center_y, center_z, radius-0.1);
	}
	else return ;
}
void renderScene(void) {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	drawCircle(cen_x,cen_y,cen_z,radius);

	glutSwapBuffers();
}

void main(int argc, char **argv) {
	// read Data
	readFile(cen_x, cen_y, cen_z, radius);

	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(500,500);
	glutCreateWindow("Hello OpenGL!");

	// register callbacks
	glutDisplayFunc(renderScene);

	// enter GLUT event processing cycle
	glutMainLoop();
}
