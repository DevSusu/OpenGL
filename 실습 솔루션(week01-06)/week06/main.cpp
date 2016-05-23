#include <string>
#include <fstream>
#include <vector>
#include <GL/glut.h>

using namespace std;

class vertex {
	friend class face;
	friend class obj;
public:
	vertex (){}
	vertex(float f1, float f2, float f3){
		pos = new float[3];
		pos[0] = f1;
		pos[1] = f2;
		pos[2] = f3;
	}
	vertex(const vertex& v){
		pos = new float[3];
		pos[0] = v.pos[0];
		pos[1] = v.pos[1];
		pos[2] = v.pos[2];
	}
	~vertex(){
		delete [] pos;
	}
	
private:
	float *pos;
};

class face {
	friend class obj;
public:
	face(vertex v1, vertex v2, vertex v3) {
		vtx[0] = new vertex(v1);
		vtx[1] = new vertex(v2);
		vtx[2] = new vertex(v3);		
		
	}
	face(const face& f){
		for(int i=0; i<3; i++){
			vtx[i] = new vertex(*f.vtx[i]);
		}
	}
	~face(){
		delete vtx[0];
		delete vtx[1];
		delete vtx[2];
	}	
	void draw(){
		
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
			glVertex3f(vtx[j]->pos[0], vtx[j]->pos[1], vtx[j]->pos[2]);
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


void main(int argc, char **argv) {

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




