//  2014-16649
//  최수빈
//
//  main.cpp
//  week05
//
//  Created by Subin_Choi on 4/4/16.
//  Copyright © 2016 DevSusu. All rights reserved.
//

#include <string>
#include <fstream>
#include <vector>
#include <GLUT/GLUT.h>

using namespace std;

class vertex {
public:
    
    vertex() {
    }
    
    vertex(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    
    void draw() {
        glVertex3f(x, y, z);
    }
    
private:
    float x,y,z;
    
};

class face {
public:
    
    face( vertex a, vertex b, vertex c ) {
        this->a = a;
        this->b = b;
        this->c = c;
    }
    
    void draw() {
        glBegin(GL_TRIANGLES);
            a.draw();
            b.draw();
            c.draw();
        glEnd();
    }
    
private:
    vertex a,b,c;
    
};

class obj {
public:
    vector<face> vFace;
    void draw(void);
    void ReadFromOBJFile(string filename);
};

void obj::draw(void)
{
    for(unsigned int i = 0; i < vFace.size(); i++){
        glColor3f((float)i/12, (float)i/12, (float)i/12);

        vFace[i].draw();
    }
    
}

void obj::ReadFromOBJFile(string filename)
{
    vector<vertex> vertices;
    ifstream input(filename);
    
    char sub;
    while( input >> sub)
    {
        if(sub == 'v')
        {
            float x,y,z;
            input >> x; input >> y; input >> z;
            
            vertices.push_back(vertex(x,y,z));
        }
        else if(sub == 'f')
        {
            int a,b,c;
            input >> a; input >> b; input >> c;

            this->vFace.push_back(face( vertices[a-1] , vertices[b-1] , vertices[c-1] ));
        }
    }
    
}

obj Cube;


void renderScene(void) {
    glEnable(GL_DEPTH_TEST);
    // Clear Color and Depth Buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Reset transformations
    glLoadIdentity();
    // Set the camera
    glTranslatef(-1.0, 0, 0);
    gluLookAt(	1.0f, 4.0f, 8.0f,
              0.0f, 0.0f,  0.0f,
              0.0f, 1.0f,  0.0f);
    
    glRotatef(20, 0.0f, 1.0f, 0.0f);
    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);
    // Set the correct perspective.
    gluPerspective(45.0f, 1.0f, 0.1f, 100.0f);
    
    Cube.draw();
    glutSwapBuffers();
}


int main(int argc, char **argv) {
    
    Cube.ReadFromOBJFile("Cube.obj");
    
    // init GLUT and create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(640,640);
    glutCreateWindow("Practice 05");
    
    // register callbacks
    glutDisplayFunc(renderScene);
    
    // enter GLUT event processing cycle
    glutMainLoop();
}
