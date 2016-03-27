//  2014-16649 최수빈
//
//  main.cpp
//  week02
//
//  Created by Subin_Choi on 3/14/16.
//  Copyright © 2016 DevSusu. All rights reserved.
//

#include "ReadFile.h"
#include <math.h>
#include <GLUT/glut.h>

#include <iostream>

double cen_x, cen_y, cen_z;
double radius;

void drawCircle(double center_x, double center_y, double center_z, double radius){
    static int count = 0;
    double step = 100;
    
    //implement color define
    glClearColor(0,0,0,1);
    glColor3f( 1, count%2, count%2 ); // color RED or WHITE

    glBegin(GL_TRIANGLE_FAN);
    glVertex3d(center_x, center_y, center_z);
    for(int i=0; i<step+1; i++){
        double x=radius*cos(2.0*M_PI/step*i);
        double y=radius*sin(2.0*M_PI/step*i);
        glVertex3d(x,y,center_z);
    }
    
    glEnd();
    
    //implement escape condition and recursive function call
    count++;
    if ( radius > 0 )
        drawCircle( center_x, center_y, center_z, radius-0.1 );
    
}
void renderScene(void) {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    drawCircle(cen_x,cen_y,cen_z,radius);
    
    glutSwapBuffers();
}

int main(int argc, char **argv) {
    
    // read Data
    readFile(cen_x, cen_y, cen_z, radius);
    
    std::cout << cen_x << cen_y << cen_z << radius;
    
    // init GLUT and create Window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("Practice 02");
    
    // register callbacks
    glutDisplayFunc(renderScene);
    
    // enter GLUT event processing cycle
    glutMainLoop();
}

