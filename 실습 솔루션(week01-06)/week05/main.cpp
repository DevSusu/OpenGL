#include <string>
#include <fstream>
#include <vector>
#include <GL/glut.h>

using namespace std;

class vertex {
public:
	vertex(){}
	vertex(float a, float b, float c):x(a),y(b),z(c){}

	float x,y,z;
};

class face {
public:
	face(){}
	face(vertex a, vertex b, vertex c){
		vtx[0] = a;
		vtx[1] = b;
		vtx[2] = c;
	}

	void draw(){
		glBegin(GL_TRIANGLES);
		for(int i=0; i<3; i++){
			glVertex3f(vtx[i].x, vtx[i].y, vtx[i].z);
		}
		glEnd();
	}

	vertex vtx[3];
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
			float a,b,c;
			input >> a >> b >> c;
			vertices.push_back(vertex(a,b,c));
		}
		else if(sub == 'f')
		{
			int a,b,c;
			input >> a >> b >> c;
			vFace.push_back(face(vertices[a-1], vertices[b-1], vertices[c-1]));
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


void main(int argc, char **argv) {

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



