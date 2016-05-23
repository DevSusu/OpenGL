// 2014-16649
// 최수빈
//  main.cpp
//  week07
//
//  Created by Subin_Choi on 4/25/16.
//  Copyright © 2016 DevSusu. All rights reserved.
//

#include <GLUT/glut.h>
#include <cmath>
#define PI 3.141592

class Position {
public:
    Position(){
        
    }
    Position(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    void move(float x, float y, float z) {
        this->x += x;
        this->y += y;
        this->z += z;
    }
    float x,y,z;
};

class Shape {
public:
    void move(float x,float y,float z) {
        pos.move(x,y,z);
    }
    void draw() {
        glColor3f(color[0], color[1], color[2]);
    };
protected:
    Position pos;
    float color[3];
};

class Rectangle : public Shape {
public:
    Rectangle() : Rectangle(0.5,0.5) {}
    Rectangle(float width, float height) {
        this->width = width;
        this->height = height;
        Shape::color[0] = 1.0; Shape::color[1] = 0; Shape::color[2] = 0;
        Shape::pos = Position(0,0,0);
    }
    void draw() {
        Shape::draw();
        glBegin(GL_QUADS);
        int direction[4][2] = { {0,0},{0,1},{1,1},{1,0} };
        for(int i=0;i<4;i++){
            glVertex3f(direction[i][0]*width+Shape::pos.x,direction[i][1]*height+Shape::pos.y,Shape::pos.z);
        }
        glEnd();
    }
private:
    float width, height;
    
};

class Circle : public Shape {
public:
    Circle() : Circle(0.25) {}
    Circle(float radius) {
        this->radius = radius;
        Shape::color[0] = 0; Shape::color[1] = 0; Shape::color[2] = 1.0;
        Shape::pos = Position(-0.5,0,0);
    }
    void draw() {
        Shape::draw();
        glBegin(GL_TRIANGLE_FAN);
        glVertex3f(Shape::pos.x, Shape::pos.y, Shape::pos.z);
        int step = 20;
        double x,y;
        for(int i=0; i<step+1; i++) {
            x=radius*cos(2.0*PI/step*i);
            y=radius*sin(2.0*PI/step*i);
            glVertex3f(Shape::pos.x+x,Shape::pos.y+y,Shape::pos.z);
        }
        glEnd();
    }
    
private:
    float radius;
    
};

Rectangle rect;
Circle cir;

void renderScene()
{
    // Clear Color and Depth Buffers
    glClearColor(1.0f,1.0f,1.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    rect.draw();
    cir.draw();
    
    glutSwapBuffers();
}

void SpecialKey(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_UP:
            rect.move(0,0.1,0);
            break;
        case GLUT_KEY_DOWN:
            rect.move(0,-0.1,0);
            break;
        case GLUT_KEY_RIGHT:
            cir.move(0.1,0,0);
            break;
        case GLUT_KEY_LEFT:
            cir.move(-0.1,0,0);
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(640,680);
    glutCreateWindow("Practice 07");
    glutSpecialFunc(SpecialKey);
    
    glutDisplayFunc(renderScene);
    glutMainLoop();
    
}
