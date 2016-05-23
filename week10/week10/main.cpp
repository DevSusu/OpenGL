// 2014-16649
// 최수빈
//
//  main.cpp
//  week10
//
//  Created by Subin_Choi on 5/16/16.
//  Copyright © 2016 DevSusu. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <GLUT/glut.h>

#define PI 3.141592
#define TIME_CONSTANT 1000

using namespace std;

class Vec3f{
public:
    Vec3f(){}
    Vec3f(float a, float b, float c){
        x = a; y = b; z = c;
    }
    //operator overloading
    Vec3f& operator=(const Vec3f& vec) {
        this->x = vec.x;
        this->y = vec.y;
        this->z = vec.z;
        return (*this);
    }
    Vec3f operator+(const Vec3f& a) {
        return Vec3f( x+a.x , y+a.y , z+a.z );
    }
    Vec3f& operator+=(const Vec3f& a) {
        (*this) = (*this) + a;
        return (*this);
    }
    Vec3f operator-(const Vec3f& a) {
        return Vec3f( x-a.x , y-a.y , z-a.z );
    }
    Vec3f& operator-=(const Vec3f& a) {
        (*this) = (*this) - a;
        return (*this);
    }
    Vec3f operator*(const float& x) const {
        return Vec3f( this->x*x,this->y*x,this->z*x );
    } // v*2.0f
    float& operator[](const size_t i){
        switch(i) {
            case 0: return x;
            case 1: return y;
            default: return z;
        }
    }
    
    float x,y,z;
};

// 2.0f*v
inline Vec3f operator*(const float& s, const Vec3f& v) {
    return v*s;
}

class dot{
public:
    //dot product functor
    float operator()( const Vec3f& a, const Vec3f& b ) {
        return a.x*b.x + a.y*b.y + a.z*b.z ;
    }
};

class Color{
public:
    Color(){
        
    }
    Color(Color& c){
        this->rgb = c.rgb;
    }
    virtual ~Color(){
        
    }
    void setRGB(float r, float g, float b){
        rgb[0] = r;
        rgb[1] = g;
        rgb[2] = b;
    }
    
    Vec3f rgb;
};

class Shape {
public:
    Shape(){
        
    }
    Shape(Shape& sha){
        velocity = sha.velocity;
        
    }
    virtual ~Shape(){
        
    }
    virtual void draw(){}
    virtual void move(){}
    
    
    Vec3f velocity;
};


class Circle : public Shape, public Color {
public:
    Circle();
    Circle(Circle& cir):Shape(cir), Color(cir){
        this->radius = cir.radius;
        this->centerPos = cir.centerPos;
    }
    ~Circle(){}
    void draw();
    void move();
    void setPosition(float x, float y, float z){
        centerPos = Vec3f(x,y,z);
    }
    Vec3f centerPos;
    float radius;
};

Circle::Circle(){
    radius = 0.25;
    
    velocity = Vec3f(float(rand()%10)/TIME_CONSTANT,float(rand()%10)/TIME_CONSTANT,0);
    velocity[2]= 0;
    rgb = Vec3f(0,0,1);
}

void Circle::draw(){
    glColor3f(rgb[0], rgb[1], rgb[2]);
    glBegin(GL_TRIANGLE_FAN);
    float step = 100;
    glVertex3f(centerPos[0], centerPos[1], centerPos[2]);
    for(int i=0; i<step+1; i++){
        float x=radius*cos(2.0*PI/step*i);
        float y=radius*sin(2.0*PI/step*i);
        glVertex3f(x+centerPos[0],y + centerPos[1],centerPos[2]);
    }
    glEnd();
}

void Circle::move(){
    centerPos += velocity;
}

vector<Circle*> cir;
void initShape(){
    Circle* shape = new Circle();
    shape->setPosition(-0.5,0,0);
    cir.push_back(shape);
    
    shape = new Circle();
    shape->setPosition(0.5,0,0);
    cir.push_back(shape);

    shape = new Circle(*shape);
    shape->setPosition(0,0.5,0);
    cir.push_back(shape);
    
}
bool collisionDetection(Circle& c1, Circle& c2){
    
    Vec3f differenceVector = c1.centerPos-c2.centerPos;
    dot dotoperator;
    float distance = sqrt(dotoperator(differenceVector, differenceVector));
    
    if(c1.radius + c2.radius > distance){
        return true;
    }
    else
        return false;
    
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
    for(int i=0; i<cir.size(); i++){
        cir[i]->move();
    }
    dot dotoperator;
    for(int i=0; i<cir.size(); i++){
        for(int j=i+1; j<cir.size(); j++){
            if(collisionDetection(*cir[i], *cir[j])){
                
                Vec3f vel_difference = cir[i]->velocity - cir[j]->velocity;
                Vec3f pos_difference = cir[i]->centerPos - cir[j]->centerPos;
                float cal = dotoperator(vel_difference, pos_difference)/dotoperator(pos_difference, pos_difference);
                cir[i]->velocity -= dotoperator(vel_difference, pos_difference)/dotoperator(pos_difference, pos_difference)*pos_difference;
                
                cir[j]->velocity += dotoperator(vel_difference, pos_difference)/dotoperator(pos_difference, pos_difference)*pos_difference;
                
            }
        }
    }
    
    for(int i=0; i<cir.size(); i++){
        if( cir[i]->centerPos[0] > 1-cir[i]->radius ) {
            cir[i]->velocity[0] *= -1;
            cir[i]->centerPos[0] = 1-cir[i]->radius;
        }
        if( cir[i]->centerPos[0] < -1+cir[i]->radius) {
            cir[i]->velocity[0] *= -1;
            cir[i]->centerPos[0] = -1+cir[i]->radius;
        }
        if( cir[i]->centerPos[1] > 1-cir[i]->radius ) {
            cir[i]->velocity[1] *= -1;
            cir[i]->centerPos[1] = 1-cir[i]->radius;
        }
        if( cir[i]->centerPos[1] < -1+cir[i]->radius ) {
            cir[i]->velocity[1] *= -1;
            cir[i]->centerPos[1] = -1+cir[i]->radius;
        }
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
    glutCreateWindow("Practice 10");
    
    glutDisplayFunc(renderScene);
    glutIdleFunc(idle);
    glutMainLoop();
    
    for(int i=0; i<cir.size(); i++){
        delete cir[i];
    }
}
