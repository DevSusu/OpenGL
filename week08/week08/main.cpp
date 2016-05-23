// 2014-16649
// 최수빈
//
//  main.cpp
//  week08
//
//  Created by Subin_Choi on 5/3/16.
//  Copyright © 2016 DevSusu. All rights reserved.
//


#include <vector>
#include <cmath>
#include <GLUT/glut.h>

#define PI 3.141592

using namespace std;

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
    virtual void move(){};
    virtual void draw(){};
    void drawColor() {
        glColor3f(color[0], color[1], color[2]);
    }
    void invertVelocity() {
        this->velocity *= -1;
    }
protected:
    Position pos;
    float color[3];
    float velocity;
};

class Circle : public Shape {
public:
    Circle() : Circle(0.25) {}
    Circle(float radius) {
        this->radius = radius;
        Shape::color[0] = 0; Shape::color[1] = 0; Shape::color[2] = 1.0;
        Shape::pos = Position(-0.5,0,0);
        Shape::velocity = 0.01;
    }
    void move() {
        Shape::pos.move(0,Shape::velocity,0);
    }
    void draw() {
        Shape::drawColor();
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

class Rectangle : public Shape {
public:
    Rectangle() : Rectangle(0.5,0.5) {}
    Rectangle(float width, float height) {
        this->width = width;
        this->height = height;
        Shape::color[0] = 1.0; Shape::color[1] = 0; Shape::color[2] = 0;
        Shape::pos = Position(0,0,0);
        Shape::velocity = 0.01;
    }
    void move() {
        Shape::pos.move(Shape::velocity,0,0);
    }
    void draw() {
        Shape::drawColor();
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

vector<Shape*> shapes;

void initShape(){
    Shape* shape = new Circle();
    shapes.push_back(shape);
    
    shape = new Rectangle();
    shapes.push_back(shape);
}

void renderScene()
{
    // Clear Color and Depth Buffers
    glClearColor(1.0f,1.0f,1.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    for(int i = 0; i < shapes.size(); i++)
        shapes[i]->draw();
    
    glutSwapBuffers();
}
void idle(){
    //call move function
    for(int i = 0; i < shapes.size(); i++)
        shapes[i]->move();
    
    
    static int count = 0; // setting direction change condition
    if( ++count % 50 == 0 ){
        //call direction change function
        for(int i = 0; i < shapes.size(); i++)
            shapes[i]->invertVelocity();
        
    }
    glutPostRedisplay(); //call display callback function
}
int main(int argc, char **argv)
{
    initShape();
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(640,680);
    glutCreateWindow("Practice 07");
    
    glutDisplayFunc(renderScene);
    glutIdleFunc(idle);
    glutMainLoop();
    
}
