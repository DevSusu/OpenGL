//  2014-16649
//  최수빈
//  main.cpp
//  week12
//
//  Created by Subin_Choi on 5/30/16.
//  Copyright © 2016 DevSusu. All rights reserved.
//


#include <ctime>
#include <vector>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <string>
#include "Vec.h"
#include <GLUT/glut.h>

#define PI 3.141592
#define TIME_CONSTANT 100
#define FPS 60
using namespace std;

int score=0;
void score_update();

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

template<typename T, typename F>
std::size_t count_color(T begin, T end, F& func) {
    //count if function using functor
    int cnt = 0;
    while( begin != end ) {
        if( func(begin) ) cnt++;
        begin++;
    }
    return cnt;
}

std::vector<Vec<float, 3>> color_array;

class Color{
public:
    Color(){
        rgb = color_array[0];
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
    void colorUpdate();
    
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


class compare_color{
public:
    compare_color(Vec<float, 3> b) : temp(b){}
    bool operator()(std::vector<Vec<float, 3>>::iterator x){
        //implement compare_color functor
        for( int i=0;i<3;i++ ) {
            if ( (*x)[i] != temp[i] ) return 0;
        }
        return 1;
    }
    bool operator()(std::vector<Circle*>::iterator x){
        //implement compare_color functor
        for( int i=0;i<3;i++ ) {
            if ( (*x)->rgb[i] != temp[i] ) return 0;
        }
        return 1;
    }
    
private:
    Vec<float, 3> temp;
};

template<typename T, typename S>
int find_index(T begin, T end, S val) {
    //return array index
    int index=0;
    compare_color comp(val);
    
    while( begin != end ) {
        
        if( comp(begin) ) return index;
        
        begin++;
        index++;
    }
    
    return index;
}

void Color::colorUpdate() {
    int index = find_index(color_array.begin(), color_array.end(), rgb);
    if(index <6)
        rgb = color_array[index+1];
}

Circle::Circle(){
    radius = 0.05;
    velocity[0] = float(rand()%10-5)/(FPS*3);
    velocity[1] = float(rand()%10-5)/(FPS*3);
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

std::vector<Circle*> cir;
Rectangle* rect;
void initShape(){
    Vec<float, 3> color;
    color[0] = 1.0f; color[1] = 0.0f; color[2] = 0.0f;
    color_array.push_back(color);
    color[0] = 1.0f; color[1] = 0.5f; color[2] = 0.0f;
    color_array.push_back(color);
    color[0] = 1.0f; color[1] = 1.0f; color[2] = 0.0f;
    color_array.push_back(color);
    color[0] = 0.0f; color[1] = 1.0f; color[2] = 0.0f;
    color_array.push_back(color);
    color[0] = 0.0f; color[1] = 0.0f; color[2] = 1.0f;
    color_array.push_back(color);
    color[0] = 75.0f/255.0f; color[1] = 0.0f; color[2] = 130.0f/255.0f;
    color_array.push_back(color);
    color[0] = 139.0f/255.0f; color[1] = 0.0f; color[2] = 1.0f;
    color_array.push_back(color);
    
    
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
    glutPrint(-0.95, 0.95, glutFonts[3], strdup(("Score: " + std::to_string(score)).c_str()), 0.0, 0,0,1);
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
                    cir[i]->colorUpdate();
                }
                else if(distance1 < cir[i]->radius || distance2 < cir[i]->radius){
                    cir[i]->velocity[1] *= -1;
                    cir[i]->centerPos[1] = rect->cornerPoint[1]+rect->length[1]+cir[i]->radius;
                    cir[i]->colorUpdate();
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
                //cir.erase(cir.begin()+i);
            }
            
            
        }
        if(cir.size() == 0){
            exit(0);
        }
        score_update();
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

void score_update(){
    //score_update
    //red = 0, orange = 1, yellow = 2, green = 3, blue = 4, Indigo = 5, Violet = 6
    int score_arr[7] = {0,1,2,3,4,5,6};
    int sum = 0;
    for(int i=0; i<color_array.size(); i++){
        compare_color comp(color_array[i]);
        sum += score_arr[ i ] * count_color(cir.begin(), cir.end(), comp );
    }
    score = sum;
}

int main(int argc, char **argv)
{
    srand(time(NULL));
    initShape();
    
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(640,680);
    glutCreateWindow("Practice 12");
    
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
