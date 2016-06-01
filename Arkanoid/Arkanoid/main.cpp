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

#define WINDOW_HALF_WIDTH 320

using namespace std;

// game settings
int stage;
int life;
int score;

bool stop = false;
bool pause = false;

vector<Rectangle*> rect;
vector<Circle*> cir;
Boundary* boundary;
Stick* stick;

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

void gameReset() {
    life = 3;
    stage = 1;
    score = 0;
    
    pause = false;
    stop = false;
}

void initBall() {
    int num = 1;
    VEL = STAGE_VEL[stage];
    for (int i = 0; i<num; i++) {
        Circle* shape = new Circle();
        shape->setPosition((BORDER_RIGHT+BORDER_LEFT)/2.0, 0);
        cir.push_back(shape);
    }
}

void initShape() {

    initBall();
    boundary = new Boundary();
    
    stick = new Stick();
    stick->setPosition((BORDER_RIGHT+BORDER_LEFT-STICK_WIDTH)/2.0, -0.95);
    stick->setlength(STICK_WIDTH,STICK_HEIGHT);
    rect.push_back(stick);
    
    Rectangle* rect_1;
    int brick_num = 12;
    for (int i = 0; i < brick_num; i++) {
        rect_1 = new Rectangle();
        rect_1->setDurability(stage);
        rect_1->setPosition(BORDER_LEFT+0.005 + (i-(i/10)*10)*(BRICK_WIDTH+0.01), 0.95-0.05*(i/10));
        rect_1->setlength(BRICK_WIDTH, BRICK_HEIGHT);
        rect.push_back(rect_1);
    }
    
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
    
    if( !pause ) {
        
        for (int i = 0; i < cir.size(); i++)
            cir[i]->draw();
        for (int i = 0; i < rect.size(); i++)
            rect[i]->draw();
        boundary->draw();
        
        glutPrint(0.65, 0.90, glutFonts[3], strdup(("Score: " + std::to_string(score)).c_str()), 0.0, 0,0,1);
        glutPrint(0.65, 0.60, glutFonts[3], strdup(("Stage: " + std::to_string(stage)).c_str()), 0.0, 0,0,1);
        glutPrint(0.65, 0.30, glutFonts[3], strdup(("Life: " + std::to_string(life)).c_str()), 0.0, 0,0,1);
        glutSwapBuffers();
        
    } else {
        
        if( stop ) {
            glutPrint(-0.15, 0.6, glutFonts[3], strdup("Game Dead"), 0.0, 0,0,1);
        } else {
            glutPrint(-0.10 , 0.6, glutFonts[3], strdup("Paused"), 0.0, 0,0,1);
            glutPrint(-0.1, -0.6 , glutFonts[3], strdup(("Life: " + std::to_string(life)).c_str()), 0.0, 0,0,1);
        }
        glutPrint(-0.1, 0.3, glutFonts[3], strdup(("Score: " + std::to_string(score)).c_str()), 0.0, 0,0,1);
        glutPrint(-0.35, 0, glutFonts[3], strdup("Press Space Bar to restart"), 0.0, 0,0,1);
        glutPrint(-0.25, -0.3, glutFonts[3], strdup("Press ESC to quit"), 0.0, 0,0,1);
        glutSwapBuffers();

    }
}

clock_t preTime;
void idle() {
    clock_t current = clock();
    clock_t diff = current - preTime;
    if (diff > 1000.0 / FPS && !pause) {
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
                if (rect[j]->collide(cir[i])) {
                    rect[j]->durability--;
                    
                    if( rect[j]->durability == 0)
                        rect.erase(rect.begin() + j);
                    
                    score++;
                }
            }
            
            // boundary
            if (boundary->collide(cir[i]) ) {
                cir.erase(cir.begin() + i);
            }
            
            if ( cir.size() == 0 ) {
                life--;
                
                if( life == 0 ) {
                    stop = true;
                }
                
                initBall();
                pause = true;
            }
            if ( rect.size() == 1 ) {
                stage++;
                if( stage == 4 ) {
                    stop = true;
                }
                cleanUp();
                initShape();
                pause = true;
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
            
        case 32: // SPACEBAR
            if( stop ) {
                stop = !stop;
                cleanUp();
                gameReset();
                initShape();
            }
            else {
                pause = !pause;
            }
            break;
            
        case 27: // ESC
            if( !pause )
                exit(0);
            break;
            
        default:
            break;
    }
    glutPostRedisplay();
}

void passive(int x, int y){
    Vec<float,2> temp;
    
    temp[0] = (x- WINDOW_HALF_WIDTH - WINDOW_HALF_WIDTH*STICK_WIDTH/2)/WINDOW_HALF_WIDTH;
    temp[1] = rect[0]->cornerPoint[1];
    
    rect[0]->moveTo( temp );
}


int main(int argc, char **argv)
{
    srand(time(NULL));
    gameReset();
    initShape();
    
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WINDOW_HALF_WIDTH * 2, 600);
    glutCreateWindow("Arkanoid");
    
    glutDisplayFunc(renderScene);
    preTime = clock();
    glutIdleFunc(idle);
    // stick movement by mouse
    glutPassiveMotionFunc(&passive);
    glutSpecialFunc(SpecialKey);
    glutMainLoop();
    
    for (int i = 0; i < cir.size(); i++) {
        delete cir[i];
    }
    for (int i = 0; i < rect.size(); i++) {
        delete rect[i];
    }
    delete boundary;
}