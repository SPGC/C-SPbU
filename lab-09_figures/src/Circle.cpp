#include <cstring>
#include <stdio.h>

#include "Circle.hpp"


Circle::Circle(int id, int x, int y, int radius, const char *label) : Figure(id, x, y){
    this->radius = radius;
    this->label = new char[strlen(label) + 1];
    strcpy(this->label, label);
}

Circle::~Circle(){
    delete [] label;
}

void Circle::print() const{
    printf("Circle %d: x = %d y = %d radius = %d label = %s\n", id, x, y, radius, label);
}

bool Circle::is_inside(int x, int y) const{
    int distance = (this->x - x) * (this->x - x) + (this->y - y) * (this->y - y);
    if(distance <= radius * radius){
        return true;
    }
    return false;
}

void Circle::zoom(int factor){
    radius*= factor;
}