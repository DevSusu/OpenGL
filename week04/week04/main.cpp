// 2014-16649
// 최수빈
//
//  main.cpp
//  week04
//
//  Created by Subin_Choi on 3/27/16.
//  Copyright © 2016 DevSusu. All rights reserved.
//

#include <GLUT/glut.h>

class Color{
public:
    float getRed(){ return r;}
    float getGreen(){ return g;}
    float getBlue(){ return b;}
    
    void setColor(float r, float g, float b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
    }
private:
    float r,g,b;
};

class plane
{
public:
    void draw(void)
    {
        //implement here - using glColor3f, glBegin(GL_QUADS), glVertex3f,
        glColor3f(color.getRed(), color.getGreen(), color.getBlue());
        
        glBegin(GL_QUADS);
        
        for (int i = 0; i < 4; i++){
            glVertex3f(v[i][0], v[i][1], v[i][2]);
        }
        
        glEnd();
        
    }
    void setColor(float r, float g, float b){
        //set plane color
        color.setColor(r,g,b);
    }
    
    void setVertex(float v[4][3]){
        //set vertex position
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 3; j++){
                this->v[i][j] = v[i][j];
            }
        }
    }
    
private:
    Color color;
    float v[4][3];
};

class box
{
public:
    void setDefault();
    void draw()
    {
        //implement here - do not use open GL function directly
        //use plane class
        int i;
        for (i = 0; i < 6; i++)
        {
            P[i].draw();
        }
    }
    
private:
    plane P[6];
};

void box::setDefault()
{
    // Setting colors and vertex positions to plane classes
    P[0].setColor(0.2f,0.7f,0.9f);
    P[1].setColor(0.5f,0.3f,0.2f);
    P[2].setColor(0.7f,0.4f,0.5f);
    P[3].setColor(0.4f,0.2f,0.8f);
    P[4].setColor(0.3f,0.6f,0.4f);
    P[5].setColor(0.8f,0.9f,0.3f);
    
    float p0_vertex[4][3];
    float p1_vertex[4][3];
    float p2_vertex[4][3];
    float p3_vertex[4][3];
    float p4_vertex[4][3];
    float p5_vertex[4][3];
    
    p0_vertex[0][0] = 2.0f;      p0_vertex[0][1] = -2.0f;   p0_vertex[0][2] = -2.0f;
    p0_vertex[1][0] = -2.0f;   p0_vertex[1][1] = -2.0f;   p0_vertex[1][2] = -2.0f;
    p0_vertex[2][0] = -2.0f;   p0_vertex[2][1] = 2.0f;      p0_vertex[2][2] = -2.0f;
    p0_vertex[3][0] = 2.0f;      p0_vertex[3][1] = 2.0f;      p0_vertex[3][2] = -2.0f;
    
    p1_vertex[0][0] = 2.0f;      p1_vertex[0][1] = -2.0f;   p1_vertex[0][2] = 2.0f;
    p1_vertex[1][0] = -2.0f;   p1_vertex[1][1] = -2.0f;   p1_vertex[1][2] = 2.0f;
    p1_vertex[2][0] = -2.0f;   p1_vertex[2][1] = 2.0f;      p1_vertex[2][2] = 2.0f;
    p1_vertex[3][0] = 2.0f;      p1_vertex[3][1] = 2.0f;      p1_vertex[3][2] = 2.0f;
    
    p2_vertex[0][0] = 2.0f;      p2_vertex[0][1] = -2.0f;   p2_vertex[0][2] = -2.0f;
    p2_vertex[1][0] = -2.0f;   p2_vertex[1][1] = -2.0f;   p2_vertex[1][2] = -2.0f;
    p2_vertex[2][0] = -2.0f;   p2_vertex[2][1] = -2.0f;   p2_vertex[2][2] = 2.0f;
    p2_vertex[3][0] = 2.0f;      p2_vertex[3][1] = -2.0f;   p2_vertex[3][2] = 2.0f;
    
    p3_vertex[0][0] = 2.0f;      p3_vertex[0][1] = 2.0f;      p3_vertex[0][2] = -2.0f;
    p3_vertex[1][0] = -2.0f;   p3_vertex[1][1] = 2.0f;      p3_vertex[1][2] = -2.0f;
    p3_vertex[2][0] = -2.0f;   p3_vertex[2][1] = 2.0f;      p3_vertex[2][2] = 2.0f;
    p3_vertex[3][0] = 2.0f;      p3_vertex[3][1] = 2.0f;      p3_vertex[3][2] = 2.0f;
    
    p4_vertex[0][0] = -2.0f;   p4_vertex[0][1] = 2.0f;      p4_vertex[0][2] = -2.0f;
    p4_vertex[1][0] = -2.0f;   p4_vertex[1][1] = -2.0f;   p4_vertex[1][2] = -2.0f;
    p4_vertex[2][0] = -2.0f;   p4_vertex[2][1] = -2.0f;   p4_vertex[2][2] = 2.0f;
    p4_vertex[3][0] = -2.0f;   p4_vertex[3][1] = 2.0f;      p4_vertex[3][2] = 2.0f;
    
    p5_vertex[0][0] = 2.0f;      p5_vertex[0][1] = 2.0f;      p5_vertex[0][2] = -2.0f;
    p5_vertex[1][0] = 2.0f;      p5_vertex[1][1] = -2.0f;   p5_vertex[1][2] = -2.0f;
    p5_vertex[2][0] = 2.0f;      p5_vertex[2][1] = -2.0f;   p5_vertex[2][2] = 2.0f;
    p5_vertex[3][0] = 2.0f;      p5_vertex[3][1] = 2.0f;      p5_vertex[3][2] = 2.0f;
    
    P[0].setVertex(p0_vertex);
    P[1].setVertex(p1_vertex);
    P[2].setVertex(p2_vertex);
    P[3].setVertex(p3_vertex);
    P[4].setVertex(p4_vertex);
    P[5].setVertex(p5_vertex);
}


void renderScene(void) {
    
    // Clear Color and Depth Buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Reset transformations
    glLoadIdentity();
    
    // Set the camera
    gluLookAt(   0.0f, 0.0f, 10.0f,
              0.0f, 0.0f,  0.0f,
              0.0f, 1.0f,  0.0f);
    
    glRotatef(20, 0.0f, 1.0f, 0.0f);
    
    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);
    
    // Set the correct perspective.
    gluPerspective(45.0f, 1.0f, 0.1f, 100.0f);
    
    // Create BOX class
    box BOX;
    BOX.setDefault();
    
    // Draw Box class
    BOX.draw();
    
    glutSwapBuffers();
}

int main(int argc, char **argv) {
    
    // init GLUT and create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(320,320);
    glutCreateWindow("Hello Cube");
    
    // register callbacks
    glutDisplayFunc(renderScene);
    
    // enter GLUT event processing cycle
    glutMainLoop();
}