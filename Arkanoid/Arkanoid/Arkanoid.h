#ifndef _ARKANOID_H_
#define _ARKANOID_H_

#define STICK_WIDTH 0.19f
#define STICK_HEIGHT 0.045f

#define TIME_CONSTANT 100
#define FPS 45

class Color {
public:
    Color() {
        
    }
    Color(Color& c) {
        this->rgb = c.rgb;
    }
    virtual ~Color() {
        
    }
    void setRGB(float r, float g, float b) {
        rgb[0] = r;
        rgb[1] = g;
        rgb[2] = b;
    }
    
    Vec<float, 3> rgb;
};

class Shape {
public:
    Shape() {
        
    }
    Shape(Shape& sha) {
        velocity = sha.velocity;
        
    }
    virtual ~Shape() {
        
    }
    virtual void draw() {}
    //virtual void move(){}
    
    Vec<float, 2> velocity;
};


class Circle : public Shape, public Color {
public:
    Circle();
    Circle(Circle& cir) :Shape(cir), Color(cir) {
        this->radius = cir.radius;
        this->centerPos = cir.centerPos;
    }
    ~Circle() {}
    void draw();
    void move();
    bool isColliding(Circle* c);
    void collide(Circle* c);
    void setPosition(float x, float y) {
        centerPos[0] = x;
        centerPos[1] = y;
    }
    Vec<float, 2> centerPos;
    float radius;
};

/********************* by Subin ************************/
bool Circle::isColliding(Circle* c) {
    Vec<float, 2> differenceVector = this->centerPos - c->centerPos;
    float distance = sqrt(dotoperator(differenceVector, differenceVector));
    
    if (this->radius + c->radius > distance)
        return true;
    else
        return false;
}

void Circle::collide(Circle* c) {
    if( !isColliding(c) ) return ;
    
    Vec<float, 2> vel_difference = this->velocity - c->velocity;
    Vec<float, 2> pos_difference = this->centerPos - c->centerPos;
    
    float cal = dotoperator(vel_difference, pos_difference) / dotoperator(pos_difference, pos_difference);
    
    this->velocity -= cal*pos_difference;
    c->velocity += cal*pos_difference;
    
    float distance = sqrt(dotoperator(pos_difference, pos_difference));
    float overlap = this->radius + c->radius - distance;
    Vec<float, 2> normalize = pos_difference / distance;
    this->centerPos += normalize*overlap / 2.0;
    c->centerPos -= normalize*overlap / 2.0;
}
/********************* by Subin ************************/

Circle::Circle() {
    radius = 0.05;
    velocity[0] = float(rand() % 10 - 5) / (FPS * 3);
    velocity[1] = float(rand() % 10 - 5) / (FPS * 3);
    rgb.val[0] = rand() % 10 / double(10);
    rgb.val[1] = rand() % 10 / double(10);
    rgb.val[2] = rand() % 10 / double(10);
}

void Circle::draw() {
    glColor3f(rgb[0], rgb[1], rgb[2]);
    glBegin(GL_TRIANGLE_FAN);
    float step = 100;
    glVertex3f(centerPos[0], centerPos[1], 0);
    for (int i = 0; i<step + 1; i++) {
        Vec<float, 2> displacement;
        displacement.val[0] = radius*cos(2.0*M_PI / step*i);
        displacement.val[1] = radius*sin(2.0*M_PI / step*i);
        
        Vec<float, 2> point = centerPos + displacement;
        glVertex3f(point[0], point[1], 0);
    }
    glEnd();
}

void Circle::move() {
    centerPos += velocity;
}

/********************* by Jeongwon ************************/
class Boundary : public Shape, public Color {
public:
    Boundary();
    Boundary(Boundary& boundary) :Shape(boundary),Color(boundary) {
    }
    bool isColliding(Circle* c);
    bool collide(Circle* c);
    ~Boundary(){}
    void draw();
};
Boundary::Boundary(){
    rgb.val[0] = 0;
    rgb.val[1] = 0;
    rgb.val[2] = 0;
}


/********************* by Subin ************************/
bool Boundary::collide(Circle* c) {
    if (c->centerPos[0] > 1 - c->radius) {
        c->velocity[0] *= -1;
        c->centerPos[0] = 1 - c->radius;
    }
    else if (c->centerPos[0] < -1 + c->radius) {
        c->velocity[0] *= -1;
        c->centerPos[0] = -1 + c->radius;
    }
    if (c->centerPos[1] > 1 - c->radius) {
        c->velocity[1] *= -1;
        c->centerPos[1] = 1 - c->radius;
    }
    
    else if (c->centerPos[1] < -1 - c->radius) {
        return true;
    }
    return false;
}
/********************* by Subin ************************/

void Boundary::draw() {
    glColor3f(rgb[0], rgb[1], rgb[2]);
    glBegin(GL_QUADS);
    
    glVertex3f(-1, 1, 0);
    glVertex3f(-1 + 0.005, 1, 0);
    glVertex3f(-1 + 0.005, -1, 0);
    glVertex3f(-1, -1, 0);
    
    glVertex3f(-1, 1, 0);
    glVertex3f(1, 1, 0);
    glVertex3f(1, 1 - 0.005, 0);
    glVertex3f(-1, 1 - 0.005, 0);
    
    glVertex3f(1, 1, 0);
    glVertex3f(1 - 0.005, 1, 0);
    glVertex3f(1 - 0.005, -1, 0);
    glVertex3f(1, -1, 0);
    
    glEnd();
}
/********************* by Jeongwon ************************/

class Rectangle : public Shape, public Color {
public:
    Rectangle();
    Rectangle(Rectangle& rect) :Shape(rect), Color(rect) {
        this->cornerPoint = rect.cornerPoint;
        this->length = rect.length;
    }
    ~Rectangle() {}
    void draw();
    void move();
    void setPosition(float x, float y) {
        cornerPoint[0] = x;
        cornerPoint[1] = y;
    }
    void setlength(float x, float y) {
        length[0] = x;
        length[1] = y;
    }
    bool collide(Circle* c); // Subin
    Vec<float, 2> cornerPoint;
    Vec<float, 2> length;
};

Rectangle::Rectangle() {
    
    rgb.val[0] = rand() % 10 / double(10);
    rgb.val[1] = rand() % 10 / double(10);
    rgb.val[2] = rand() % 10 / double(10);
}

void Rectangle::draw() {
    glColor3f(rgb[0], rgb[1], rgb[2]);
    glBegin(GL_QUADS);
    
    glVertex3f(cornerPoint[0], cornerPoint[1], 0);
    glVertex3f(cornerPoint[0] + length[0], cornerPoint[1], 0);
    glVertex3f(cornerPoint[0] + length[0], cornerPoint[1] + length[1], 0);
    glVertex3f(cornerPoint[0], cornerPoint[1] + length[1], 0);
    
    glEnd();
}

/********************* by Jeongwon ************************/
void Rectangle::move() {
    Vec<float, 2> m;
    cornerPoint += m;
}
/********************* by Jeongwon ************************/

/********************* by Subin ************************/
bool Rectangle::collide(Circle* c) {
    
    bool collide_top = c->centerPos[1] - c->radius < this->cornerPoint[1] + this->length[1];
    bool collide_bottom = c->centerPos[1] + c->radius > this->cornerPoint[1];
    bool collide_left = c->centerPos[0] + c->radius > this->cornerPoint[0];
    bool collide_right = c->centerPos[0] - c->radius < this->cornerPoint[0] + this->length[0];
    
    if( !(collide_top && collide_left && collide_right && collide_bottom) ) return false;
        
    if( c->velocity[1] < 0  ) {
        
        if( c->centerPos[0] > this->cornerPoint[0] &&
            c->centerPos[0] < this->cornerPoint[0] + this->length[0] ) {
            
            c->velocity[1] *= -1;
            c->centerPos[1] = this->cornerPoint[1] + this->length[1] + c->radius;
        }
        else {
            if( c->centerPos[0] < this->cornerPoint[0] ){
                c->centerPos[0] = this->cornerPoint[0] - c->radius;
            } else {
                c->centerPos[0] = this->cornerPoint[0] + this->length[0] + c->radius;
            }
            c->velocity[0] *= -1;
        }
        
    }
    else
    {
        if( c->centerPos[0] > this->cornerPoint[0] &&
           c->centerPos[0] < this->cornerPoint[0] + this->length[0] ) {
            
            c->velocity[1] *= -1;
            c->centerPos[1] = this->cornerPoint[1] - c->radius;
        }
        else {
            if( c->centerPos[0] < this->cornerPoint[0] ){
                c->centerPos[0] = this->cornerPoint[0] - c->radius;
            } else {
                c->centerPos[0] = this->cornerPoint[0] + this->length[0] + c->radius;
            }
            c->velocity[0] *= -1;
        }
    }
    return true;
    
}
/********************* by Subin ************************/


#endif