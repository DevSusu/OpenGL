//
//  2014-16649
//  최수빈
//
//  main.cpp
//  week11
//
//  Created by Subin_Choi on 5/23/16.
//  Copyright © 2016 DevSusu. All rights reserved.
//

#include <iostream>
#include <ctime>
#include <vector>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <GLUT/glut.h>

#define PI 3.141592
#define TIME_CONSTANT 100
#define FPS 60
using namespace std;

template<typename T, int DIM>
class Vec{
public:
    Vec(){}
    
    Vec<T,DIM> operator+(const Vec& a) {
        Vec<T,DIM> temp;
        for(int i=0; i<DIM; i++){
            temp.val[i] = val[i] + a.val[i];
        }
        return temp;
    }
    Vec<T,DIM> operator-(const Vec& a) {
        Vec<T,DIM> temp;
        for(int i=0; i<DIM; i++){
            temp.val[i] = val[i] - a.val[i];
        }
        return temp;
    }
    Vec<T,DIM> operator*(const float& a) {
        Vec<T,DIM> temp;
        for(int i=0; i<DIM; i++){
            temp.val[i] = val[i] * a;
        }
        return temp;
    }
    Vec<T,DIM> operator/(const float& a) {
        Vec<T,DIM> temp;
        for(int i=0; i<DIM; i++){
            temp.val[i] = val[i] / a;
        }
        return temp;
    }
    
    //operator overloading
    Vec<T,DIM>& operator=(const Vec& a) {
        for(int i=0; i<DIM; i++){
            val[i] = a.val[i];
        }
        return *this;
    }
    Vec<T,DIM>& operator+=(const Vec& a) {
        *this = *this + a;
        return *this;
    }
    Vec<T,DIM>& operator-=(const Vec& a) {
        *this = *this - a;
        return *this;
    }
    
    
    T& operator[](const size_t i){
        return val[i];
    }
    
    T val[DIM];
};
template<typename T, int DIM>
Vec<T,DIM> operator*(const float& s, const Vec<T,DIM>& v){
    Vec<T,DIM> temp;
    for(int i=0; i<DIM; i++){
        temp.val[i] = s * v.val[i];
    }
    return temp;
}

template<typename T, int DIM>
T dotoperator(Vec<T,DIM> vec1, Vec<T,DIM> vec2){
    //function template
    T sum = 0;
    for( int i=0; i<DIM; i++ ) {
        sum += vec1[i] * vec2[i];
    }
    return sum;
}

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
    
    Vec<float, 3> rgb;
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
    
    
    Vec<float,2> velocity;
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
    void setPosition(float x, float y){
        centerPos[0] = x;
        centerPos[1] = y;
    }
    Vec<float,2> centerPos;
    float radius;
};

Circle::Circle(){
    radius = 0.05;
    velocity[0] = float(rand()%10-5)/(FPS*3);
    velocity[1] = float(rand()%10-5)/(FPS*3);
    rgb.val[0] = rand()%10/double(10);
    rgb.val[1] = rand()%10/double(10);
    rgb.val[2] = rand()%10/double(10);
}

void Circle::draw(){
    glColor3f(rgb[0], rgb[1], rgb[2]);
    glBegin(GL_TRIANGLE_FAN);
    float step = 100;
    glVertex3f(centerPos[0], centerPos[1], 0);
    for(int i=0; i<step+1; i++){
        Vec<float,2> displacement;
        displacement.val[0] = radius*cos(2.0*PI/step*i);
        displacement.val[1] = radius*sin(2.0*PI/step*i);
        
        Vec<float,2> point = centerPos + displacement;
        glVertex3f(point[0], point[1], 0);
    }
    glEnd();
}

void Circle::move(){
    centerPos += velocity;
}


class Rectangle : public Shape, public Color {
public:
    Rectangle();
    Rectangle(Rectangle& rect):Shape(rect), Color(rect){
        this->cornerPoint = rect.cornerPoint;
        this->length = rect.length;
    }
    ~Rectangle(){}
    void draw();
    void move(){}
    void move(Vec<float, 2> m){
        cornerPoint += m;
    }
    void setPosition(float x, float y){
        cornerPoint[0] = x;
        cornerPoint[1] = y;
    }
    Vec<float,2> cornerPoint;
    Vec<float,2> length;
};

Rectangle::Rectangle(){
    length[0] = 0.4;
    length[1] = 0.02;
    
    rgb.val[0] = rand()%10/double(10);
    rgb.val[1] = rand()%10/double(10);
    rgb.val[2] = rand()%10/double(10);
}


void Rectangle::draw(){
    glColor3f(rgb[0], rgb[1], rgb[2]);
    glBegin(GL_QUADS);
    
    glVertex3f(cornerPoint[0], cornerPoint[1], 0);
    glVertex3f(cornerPoint[0]+length[0], cornerPoint[1], 0);
    glVertex3f(cornerPoint[0]+length[0], cornerPoint[1]+length[1], 0);
    glVertex3f(cornerPoint[0], cornerPoint[1]+length[1], 0);
    
    glEnd();
}


vector<Circle*> cir;
Rectangle* rect;
void initShape(){
    int num = 10;
    for(int i=0; i<num; i++){
        Circle* shape = new Circle();
        shape->setPosition((rand()%num/double(num)-0.4)*2,(rand()%num/double(num)-0.4)*2);
        cir.push_back(shape);
    }
    rect = new Rectangle();
    rect->setPosition(-0.2,-0.95);
    
}

bool collisionDetection(Circle& c1, Circle& c2){
    Vec<float, 2> differenceVector = c1.centerPos-c2.centerPos;
    float distance = sqrt(dotoperator(differenceVector, differenceVector));
    
    if(c1.radius + c2.radius > distance)
        return true;
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
    rect->draw();
    glutSwapBuffers();
}

clock_t preTime;
void idle(){
    clock_t current = clock();
    clock_t diff = current - preTime;
    if(diff > 1000.0/FPS){
        for(int i=0; i<cir.size(); i++){
            cir[i]->move();
        }
        
        
        for(int i=0; i<cir.size(); i++){
            for(int j=i+1; j<cir.size(); j++){
                if(collisionDetection(*cir[i], *cir[j])){
                    
                    Vec<float, 2> vel_difference = cir[i]->velocity - cir[j]->velocity;
                    Vec<float, 2> pos_difference = cir[i]->centerPos - cir[j]->centerPos;
                    
                    float cal = dotoperator(vel_difference, pos_difference)/dotoperator(pos_difference, pos_difference);
                    
                    cir[i]->velocity -= cal*pos_difference;
                    cir[j]->velocity += cal*pos_difference;
                    
                    float distance = sqrt(dotoperator(pos_difference,pos_difference));
                    float overlap = cir[i]->radius + cir[j]->radius - distance;
                    Vec<float,2> normalize = pos_difference / distance;
                    cir[i]->centerPos += normalize*overlap/2.0;
                    cir[j]->centerPos -= normalize*overlap/2.0;
                    
                }
            }
        }
        
        
        
        for(int i=0; i<cir.size(); i++){
            
            if(cir[i]->centerPos[1] < rect->cornerPoint[1]+rect->length[1]+cir[i]->radius && cir[i]->centerPos[1] > rect->cornerPoint[1]-cir[i]->radius){
                Vec<float, 2> distanceCorner1 = cir[i]->centerPos - rect->cornerPoint;
                Vec<float, 2> distanceCorner2 = distanceCorner1;
                distanceCorner2[0] -= rect->length[0];
                float distance1 = sqrt(dotoperator(distanceCorner1, distanceCorner1));
                float distance2 = sqrt(dotoperator(distanceCorner2, distanceCorner2));
                if(cir[i]->centerPos[0]  > rect->cornerPoint[0] && cir[i]->centerPos[0] < rect->cornerPoint[0] + rect->length[0]){
                    cir[i]->velocity[1] *= -1;
                    cir[i]->centerPos[1] = rect->cornerPoint[1]+rect->length[1]+cir[i]->radius;
                }
                else if(distance1 < cir[i]->radius || distance2 < cir[i]->radius){
                    cir[i]->velocity[1] *= -1;
                    cir[i]->centerPos[1] = rect->cornerPoint[1]+rect->length[1]+cir[i]->radius;
                }
            }
            
            if(cir[i]->centerPos[0] > 1-cir[i]->radius){
                cir[i]->velocity[0] *= -1;
                cir[i]->centerPos[0] = 1-cir[i]->radius;
            }
            else if(cir[i]->centerPos[0] < -1+cir[i]->radius){
                cir[i]->velocity[0] *= -1;
                cir[i]->centerPos[0] = -1+cir[i]->radius;
                
            }
            if(cir[i]->centerPos[1] > 1-cir[i]->radius){
                cir[i]->velocity[1] *= -1;
                cir[i]->centerPos[1] = 1-cir[i]->radius;
            }
            
            else if(cir[i]->centerPos[1] < -1-cir[i]->radius){
                cir.erase(cir.begin()+i);
            }
            
        }
        if(cir.size() == 0){
            exit(0);
        }
        preTime = current;
    }
    glutPostRedisplay();
}


void SpecialKey(int key, int x, int y)
{
    Vec<float ,2> move;
    move[0] = 0.05;
    move[1] = 0;
    switch(key)
    {
            
            
        case GLUT_KEY_RIGHT:
            rect->cornerPoint += move;
            break;
        case GLUT_KEY_LEFT:
            rect->cornerPoint -= move;
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
    glutInitWindowPosition(100,100);
    glutInitWindowSize(640,680);
    glutCreateWindow("Practice 11");
    
    glutDisplayFunc(renderScene);
    preTime = clock();
    glutIdleFunc(idle);
    glutSpecialFunc(SpecialKey);
    glutMainLoop();
    
    for(int i=0; i<cir.size(); i++){
        delete cir[i];
    }	
    delete rect;
}
