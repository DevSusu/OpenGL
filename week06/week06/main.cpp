// 2014-16649
// 최수빈
//
//  main.cpp
//  week06
//
//  Created by Subin_Choi on 4/11/16.
//  Copyright © 2016 DevSusu. All rights reserved.
//

#include <string>
#include <fstream>
#include <vector>
#include <GLUT/glut.h>

#include <math.h>

using namespace std;

class vertex {
    
    friend class face;
    
public:
    //implement constructor, copy construct, destructor and member function if you need.

    vertex(const vertex& vtx) {
        this->pos = new float[3];
        for(int i=0;i<3;i++) {
            this->pos[i] = vtx.pos[i];
        }
    }
    vertex( float f1, float f2, float f3 ) {
        this->pos = new float[3];
        this->pos[0] = f1; this->pos[1] = f2; this->pos[2] = f3;
    }
    
    float* position() {
        return this->pos;
    }
    
    ~vertex() {
        delete [] pos;
    }
    
private:
    float *pos;
};

class face {
    
public:
    //implement constructor, copy construct, destructor and member function if you need.
    face( vertex v1, vertex v2, vertex v3 ){
        vtx[0] = new vertex(v1);
        vtx[1] = new vertex(v2);
        vtx[2] = new vertex(v3);
    }
    
    void draw(){
        //calculate face normal. cross product
        //you can modify this function if you need.
        float vec1[3], vec2[3], normal[3];
        for(int i=0; i<3; i++){
            vec1[i] = vtx[1]->pos[i] - vtx[0]->pos[i];
            vec2[i] = vtx[2]->pos[i] - vtx[0]->pos[i];
        }
        
        normal[0] = vec1[1]*vec2[2] - vec1[2]*vec2[1];
        normal[1] = vec1[2]*vec2[0] - vec1[0]*vec2[2];
        normal[2] = vec1[0]*vec2[1] - vec1[1]*vec2[0];
        
        float length = sqrt(normal[0]*normal[0] + normal[1]*normal[1] + normal[2]*normal[2]);
        
        glBegin(GL_TRIANGLES);
        for(int j=0; j<3; j++){
            glNormal3f(normal[0]/length, normal[1]/length, normal[2]/length);
            glVertex3f(vtx[j]->position()[0], vtx[j]->position()[1], vtx[j]->position()[2]);
        }
        glEnd();
    }
    
private:
    vertex* vtx[3];
};

class obj {
public:
    vector<face> vFace;
    void draw(void);
    void ReadFromOBJFile(string filename);
};

void obj::draw(void)
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    float lightPos[4] = {-2,5,4,0};
    float lightKa[4] = {1, 1, 1, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    GLfloat mat_d[] = {1, 1, 0, 1.0};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_d);
    for(unsigned int i = 0; i < vFace.size(); i++){
        vFace[i].draw();
    }
    
}

void obj::ReadFromOBJFile(string filename)
{
    vector<vertex> vertices;
    ifstream input(filename);
    int normal_count = 0;
    
    char sub;
    while( input >> sub)
    {
        if(sub == 'v')
        {
            float f1,f2,f3;
            input >> f1 >> f2 >> f3;
            vertices.push_back( vertex(f1, f2, f3) );
        }
        else if(sub == 'f')
        {
            int i1, i2, i3;
            input >> i1 >> i2 >> i3;
            face f( vertices[i1-1],  vertices[i2-1],  vertices[i3-1]);
            vFace.push_back(f);
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
    glutCreateWindow("Drawing cube from obj");
    
    // register callbacks
    glutDisplayFunc(renderScene);
    
    // enter GLUT event processing cycle
    glutMainLoop();
}




