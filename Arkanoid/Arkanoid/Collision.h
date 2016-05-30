#ifndef _COLLISION_H_
#define _COLLISION_H_


bool collisionDetection(Circle& c1, Circle& c2) {
    Vec<float, 2> differenceVector = c1.centerPos - c2.centerPos;
    float distance = sqrt(dotoperator(differenceVector, differenceVector));
    
    if (c1.radius + c2.radius > distance)
        return true;
    else
        return false;
}
bool collisionDetection(Rectangle& rec, Circle& c2) {
    return true;
}

void collide(Circle& c1, Circle& c2) {
    Vec<float, 2> vel_difference = c1.velocity - c2.velocity;
    Vec<float, 2> pos_difference = c1.centerPos - c2.centerPos;
    
    float cal = dotoperator(vel_difference, pos_difference) / dotoperator(pos_difference, pos_difference);
    
    c1.velocity -= cal*pos_difference;
    c2.velocity += cal*pos_difference;
    
    float distance = sqrt(dotoperator(pos_difference, pos_difference));
    float overlap = c1.radius + c2.radius - distance;
    Vec<float, 2> normalize = pos_difference / distance;
    c1.centerPos += normalize*overlap / 2.0;
    c2.centerPos -= normalize*overlap / 2.0;
}


#endif