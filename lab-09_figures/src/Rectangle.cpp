#include <stdio.h>
#include <math.h>

#include "Rectangle.hpp"


Rectangle::Rectangle(int id, int x, int y, int width, int height) : Figure(id, x, y){
    this->width = width;
    this->height = height;
}

void Rectangle::print() const{
    printf("Rectangle %d: x = %d y = %d width = %d height = %d\n", id, x, y, width, height);
}
bool Rectangle::is_inside(int x, int y) const{
    if(2 * abs(this->x - x) <= width && 2 * abs(this->y - y) <= height){
        return true;
    }
    return false;
}
void Rectangle::zoom(int factor){
    height*= factor;
    width*= factor;
}

