// 2014-16649
// 최수빈
//
//  practice_03.cpp
//  week03
//
//  Created by Subin_Choi on 3/21/16.
//  Copyright © 2016 DevSusu. All rights reserved.
//

#include <GLUT/glut.h>
#include "triangle.h"

float** position; //data to save vertices position.

void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glColor3f(1, 1, 1);
    glBegin(GL_TRIANGLES);
    
    for (int i=0;i<3;i++) {
        glVertex3f(position[i][0], position[i][1], position[i][2]);
    }

    glEnd();
    
    glutSwapBuffers();
}

int main(int argc, char **argv) {
    
    position = new float*[3];
    
    for (int i=0;i<3;i++) {
        position[i] = new float[3];
    }
    
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
}

