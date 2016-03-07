//
//  2014-16649 최수빈
//
//  main.cpp
//
//  Created by Subin_Choi on 3/7/16.
//  Copyright © 2016 DevSusu. All rights reserved.
//

#include <stdlib.h>
#include <math.h>

#include <GLUT/GLUT.h>

float radian(double degrees) {
    return degrees * (M_PI / 180.0);
}

void displayCB(void)		/* function called whenever redisplay needed */
{
    float radius = 0.5;
    float center_x = 0, center_y = 0, center_z = 0;
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1,0,0); // color RED
    
    
    glBegin(GL_TRIANGLE_FAN);
    
    glVertex3f(center_x, center_y, center_z); // center
    
    float angle = radian(36);
    for( int i=0;i<11;i++ ) {
        glVertex3f( center_x + radius*cosf(i*angle) , center_y + radius*sinf(i*angle) , center_z );
    }

    glEnd();
    glutSwapBuffers();
}

int main(int argc, char *argv[])
{
    int win;
    
    glutInit(&argc, argv);		/* initialize GLUT system */
    
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("Hello OpenGL!");
    
    /* from this point on the current window is win */
    glutDisplayFunc(displayCB);		/* set window's display callback */
    
    glutMainLoop();			/* start processing events... */
    
    /* execution never reaches this point */
    
    return 0;
}