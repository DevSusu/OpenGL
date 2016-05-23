//  2014-16649
//  최수빈
//
//  main.cpp
//  week09
//
//  Created by Subin_Choi on 5/9/16.
//  Copyright © 2016 DevSusu. All rights reserved.
//

#include <vector>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <GLUT/glut.h>

#define PI 3.141592
#define TIME_CONSTANT 1000

using namespace std;

class Position {
public:
    Position() {
        this->position = new float[3];
    }
    ~Position() {
        delete[] position;
    }
    void setPosition(float x,float y,float z) {
        position[0] = x;
        position[1] = y;
        position[2] = z;
    }
    void move(float* velocity) {
        for(int i=0;i<3;i++) {
            position[i] += velocity[i];
        }
    }
    float getDistance(Position& p) {
        return sqrt( pow(p.position[0]-this->position[0],2.0) + pow(p.position[1]-this->position[1],2.0) );
    }
    float getX() {
        return position[0];
    }
    float getY() {
        return position[1];
    }
    float getZ() {
        return position[2];
    }
    
    float* position;
};

class Color{
public:
    Color(){
        rgb = new float[3];
    }
    virtual ~Color(){
        delete [] rgb;
    }
    
    void setRGB(float r, float g, float b){
        rgb[0] = r;
        rgb[1] = g;
        rgb[2] = b;
    }
    
    void draw() {
        glColor3f(rgb[0], rgb[1], rgb[2]);
    }
    
    float* rgb;
};

class Shape {
public:
    Shape(){
        velocity = new float[3];
        velocity[0] = 0.01;
        velocity[1] = -0.01;
        velocity[2] = 0;
    }
    virtual ~Shape(){
        delete [] velocity;
    }
    void setPosition(float x,float y,float z) {
        position.setPosition(x, y, z);
    }
    void move() {
        position.move(velocity);
    }
    virtual void draw() {
    }
    
    Position position;
    float *velocity;
};

class Boundary : public Shape {
public:
    Boundary() {}
};

class Circle : public Shape, public Color {
public:
    Circle() {
        this->radius = 0.2;
        Color::setRGB(0, 0, 1);
    }
    ~Circle() {
        
    }
    void draw() {
        Color::draw();
        glBegin(GL_TRIANGLE_FAN);
        glVertex3f(Shape::position.getX(), Shape::position.getY(), Shape::position.getZ());
        int step = 20;
        double x,y;
        for(int i=0; i<step+1; i++) {
            x=radius*cos(2.0*PI/step*i);
            y=radius*sin(2.0*PI/step*i);
            glVertex3f(Shape::position.getX()+x,Shape::position.getY()+y,Shape::position.getZ());
        }
        glEnd();
    }
    void collideBoundary() {
        float x = position.getX();
        if ( x > 1.0-radius || x < -1.0+radius ) velocity[0] *= -1;
        x = x > 1.0-radius ? 1.0-radius : x;
        x = x < -1.0+radius ? -1.0+radius : x;
        
        float y = position.getY();
        if ( y > 1.0-radius || y < -1.0+radius ) velocity[1] *= -1;
        y = y > 1.0-radius ? 1.0-radius : y;
        y = y < -1.0+radius ? -1.0+radius : y;
    }
    bool collideCircle(Circle& c) {
        if ( radius + c.radius >= 0.05 + position.getDistance(c.position) )
        {
            float distance = position.getDistance(c.position);
            float x = (velocity[0]-c.velocity[0])*(position.getX()-c.position.getX());
            x += (velocity[1]-c.velocity[1])*(position.getY()-c.position.getY());
            x /= pow(distance,2.0);
            
            velocity[0] -= x * (position.getX() - c.position.getX());
            velocity[1] -= x * (position.getY() - c.position.getY());
            
            c.velocity[0] += x * (position.getX() - c.position.getX());
            c.velocity[1] += x * (position.getY() - c.position.getY());
            
            return true;
        }
        return false;
    }
    
    float radius;
};

vector<Circle*> cir;
void initShape(){
    Circle* shape = new Circle();
    shape->setPosition(-0.5,0,0);
    cir.push_back(shape);
    
    shape = new Circle();
    shape->setPosition(0.5,0,0);
    cir.push_back(shape);
    
    shape = new Circle();
    shape->setPosition(0,0.5,0);
    cir.push_back(shape);
    
}

//float getDistance()

bool collisionDetection(Circle& c1, Circle& c2){
    
    return c1.collideCircle(c2);
}

void renderScene()
{
    // Clear Color and Depth Buffers
    glClearColor(1.0f,1.0f,1.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    for(int i = 0; i < cir.size(); i++)
        cir[i]->draw();
    
    glutSwapBuffers();
}
void idle(){
    //move circle
    for(int i=0; i<cir.size(); i++){
        cir[i]->move();
    }
    
    //collisionDetection (Circle - Circle)
    for(int i=0; i<cir.size(); i++){
        for(int j=i+1; j<cir.size(); j++){
            if(collisionDetection(*cir[i], *cir[j])){
                //collision Resolution (Circle - Circle)
                // implemented in Circle::colideCircle
            }
        }
    }
    
    //collision Detection (Circle - Boundary)
    for(int i=0; i<cir.size(); i++){
        //collision Resolution (Circle - Boundary)
        cir[i]->collideBoundary();
    }
    
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    srand(time(NULL));
    initShape();
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(640,680);
    glutCreateWindow("Practice 09");
    
    glutDisplayFunc(renderScene);
    glutIdleFunc(idle);
    glutMainLoop();
    
    for(int i=0; i<cir.size(); i++){
        delete cir[i];
    }
}
