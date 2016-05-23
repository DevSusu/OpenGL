//
//  main.cpp
//  brick
//
//  Created by Subin_Choi on 3/16/16.
//  Copyright © 2016 DevSusu. All rights reserved.
//
//

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <GLUT/glut.h>

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 700

class brick {
    
};

class Bar {
    
public:
    void Draw() {
        
        glEnable(GL_POINT_SMOOTH);
        glPointSize(half_height);
        
        glBegin(GL_POINTS);
            glVertex2f(pos_x - half_width, pos_y);
            glVertex2f(pos_x + half_width, pos_y);
        glEnd();
        
        glLineWidth(2*half_height);
        
        glBegin(GL_LINES);
            glVertex2f(pos_x - half_width, pos_y);
            glVertex2f(pos_x + half_width, pos_y);
        glEnd();
        
    }
    void setPosition(float x, float y) {
        pos_x = x;
        pos_y = y;
    }
    void move(bool direction) {
        pos_x += direction ? -0.05f : +0.05f;
        pos_x = pos_x < (1.0-half_width) ? pos_x : 1.0-half_width;
        pos_x = pos_x > (-1.0+half_width) ? pos_x : -1.0+half_width;
        glutPostRedisplay();
    }
    
private:
    float vel;
    const float half_width  = 0.1;
    const float half_height = 5;
    float pos_x,pos_y;
    bool direction;

};

Bar bar;

void renderScene(void) {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glClearColor(0, 0, 0, 1);
    glColor3f(1, 0, 0);
    
    bar.Draw();
    
    glEnable(GL_POINT_SMOOTH);
    glPointSize(5.0);
    
    glBegin(GL_POINTS);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2i(0, 1);
        glVertex2i(1, 1);
    glEnd();
    
    glLineWidth(10.0);
    
    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2i(0, 1);
    glVertex2i(1, 1);
    glEnd();
    
    glBegin( GL_QUADS );
    glVertex2i(100, 100);
    glVertex2i(150, 100);
    glVertex2i(150, 150);
    glVertex2i(100, 150);
    glEnd();
    
    glutSwapBuffers();
}

void keyCB(unsigned char key, int x, int y)	/* called on key press */
{
    switch (key) {
        case 'q' : exit(0);
        case GLUT_KEY_LEFT : // G button
            bar.move(true);
            break;
        case GLUT_KEY_RIGHT : // F button
            bar.move(false);
            break;
    }
}

int main(int argc, char **argv) {
    
    bar.setPosition( 0, -0.7 );
    
    // init GLUT and create Window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,50);
    glutInitWindowSize(WINDOW_WIDTH ,WINDOW_HEIGHT);
    glutCreateWindow("Brick Breaker");
    
    // register callbacks
    glutDisplayFunc(renderScene);
    glutKeyboardFunc(keyCB);
    
    // enter GLUT event processing cycle
    glutMainLoop();
}

