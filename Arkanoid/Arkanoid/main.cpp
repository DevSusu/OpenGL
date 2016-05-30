//
//  Programming Methodology Arkanoid Project
//
//  Created on 5/05/16 by 조정원, 정병수, 최수빈
//  Copyright © 2016 DevSusu. All rights reserved.
//

#include <iostream>
#include <ctime>
#include <vector>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <GLUT/glut.h>
#include "Vec.h"
#include "Arkanoid.h"

using namespace std;

vector<Circle*> cir;
bool stop;
Stick* stick;
int score = 0;

/********************* by Jeongwon ************************/
vector<Rectangle*> rect;
Boundary* boundary;
/********************* by Jeongwon ************************/

void* glutFonts[7] = {
    GLUT_BITMAP_9_BY_15,
    GLUT_BITMAP_8_BY_13,
    GLUT_BITMAP_TIMES_ROMAN_10,
    GLUT_BITMAP_TIMES_ROMAN_24,
    GLUT_BITMAP_HELVETICA_10,
    GLUT_BITMAP_HELVETICA_12,
    GLUT_BITMAP_HELVETICA_18
};

void glutPrint(float x, float y, void* font, char* text, float r, float g, float b, float a)
{
    if(!text || !strlen(text)) return;
    bool blending = false;
    if(glIsEnabled(GL_BLEND)) blending = true;
    glEnable(GL_BLEND);
    glColor4f(r,g,b,a);
    glRasterPos2f(x,y);
    
    while (*text) {
        glutBitmapCharacter(font, *text);
        text++;
    }
    if(!blending) glDisable(GL_BLEND);
}

void initShape() {
    int num = 1;
    
    for (int i = 0; i<num; i++) {
        Circle* shape = new Circle();
        shape->setPosition(0, 0);
        cir.push_back(shape);
    }
    
    boundary = new Boundary();
    
    /********************* by Jeongwon ************************/
    stick = new Stick();
    stick->setPosition(-0.2, -0.95);
    stick->setlength(STICK_WIDTH,STICK_HEIGHT);
    rect.push_back(stick);
    
    Rectangle* rect_1;
    int brick_num = 24;
    for (int i = 0; i < brick_num; i++) {
        rect_1 = new Rectangle();
        rect_1->setPosition(-1+0.005 + (i-(i/10)*10)*0.2, 0.95-0.05*(i/10));
        rect_1->setlength(BRICK_WIDTH, BRICK_HEIGHT);
        rect.push_back(rect_1);
    }
    /********************* by Jeongwon ************************/
    
}

void cleanUp()
{
    size_t size = cir.size();
    for (int i = 0; i < size; i++) {
        delete cir[i];
    }
    size = rect.size();
    for (int i = 0; i < size; i++) {
        delete rect[i];
    }
    cir.erase(cir.begin(),cir.end());
    rect.erase(rect.begin(),rect.end());
    delete boundary;
}

void renderScene()
{
    // Clear Color and Depth Buffers
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
    if ( stop ) {
        cleanUp();
        initShape();
        
        stop = false;
        return ;
    }
    
    for (int i = 0; i < cir.size(); i++)
        cir[i]->draw();
    for (int i = 0; i < rect.size(); i++)
        rect[i]->draw();
    boundary->draw();
    
    glutPrint(0.75, 0.95, glutFonts[3], strdup(("Score: " + std::to_string(score)).c_str()), 0.0, 0,0,1);
    glutSwapBuffers();
}

clock_t preTime;
void idle() {
    clock_t current = clock();
    clock_t diff = current - preTime;
    if (diff > 1000.0 / FPS) {
        for (int i = 0; i<cir.size(); i++) {
            cir[i]->move();
        }
        
        for (int i = 0; i<cir.size(); i++) {
            for (int j = i + 1; j<cir.size(); j++) {
                cir[i]->collide(cir[j]);
            }
        }
        
        for (int i = 0; i < cir.size(); i++) {
            
            // stick
            stick->collide(cir[i]);
            
            // bricks
            for (int j = 1; j<rect.size(); j++) {
                if ( rect[j]->collide(cir[i]) ) {
                    rect.erase(rect.begin() + j);
                    score ++ ;
                }
            }
            
            // boundary
            if (boundary->collide(cir[i]) ) {
                cir.erase(cir.begin() + i);
            }
            
            if ( cir.size() == 0 || rect.size() == 1 ) {
                stop = true;
                break;
            }
            preTime = current;
        }
    }
    glutPostRedisplay();
}


void SpecialKey(int key, int x, int y)
{
    Vec<float, 2> move;
    move[0] = 0.05;
    move[1] = 0;
    switch (key)
    {
        case GLUT_KEY_RIGHT:
            rect[0]->move(move);
            break;
        case GLUT_KEY_LEFT:
            move = move * -1;
            rect[0]->move(move);
            break;
        default:
            break;
    }
    glutPostRedisplay();
}


int main(int argc, char **argv)
{
    srand(time(NULL));
    initShape();
    
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 680);
    glutCreateWindow("Practice 11");
    
    glutDisplayFunc(renderScene);
    preTime = clock();
    glutIdleFunc(idle);
    glutSpecialFunc(SpecialKey);
    glutMainLoop();
    
    for (int i = 0; i < cir.size(); i++) {
        delete cir[i];
    }
    /********************* by Jeongwon ************************/
    for (int i = 0; i < rect.size(); i++) {
        delete rect[i];
    }
    delete boundary;
    /********************* by Jeongwon ************************/
}