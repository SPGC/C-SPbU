#include <stdexcept>

#include "Scheme.hpp"


Scheme::Scheme(int capacity){
    figures = new Figure*[capacity];
    size = 0;

} 

Scheme::~Scheme(){
    for(int i = 0; i < size; i++){
        delete figures[i];
    }
    delete [] figures;
}

void Scheme::push_back_figure(Figure* fg){
    figures[size] = fg;
    size++;
}

void Scheme::remove_figure(int id){
    int index = getIndexOfFigure(id);
    if(index == -1){
        return;
    }
    delete figures[index];
    for(int i = index; i < size - 1; i++){
        figures[i] = figures[i + 1];
    }
    size--;
} 

void Scheme::print_all_figures(){
    for(int i = 0; i < size; i++){
        figures[i]->print();
    }
}

void Scheme::zoom_figure(int id, int factor){
    int index = getIndexOfFigure(id);
    if(index == -1){
        return;
    }
    figures[index]->zoom(factor);
}

Figure* Scheme::is_inside_figure(int x, int y){
    for(int i = 0; i < size; i++){
        if(figures[i]->is_inside(x,y)){
            return figures[i];
        }
    }
    return NULL;
}

void Scheme::move(int id, int new_x, int new_y){
    int index = getIndexOfFigure(id);
    if(index == -1){
        return;
    }
    figures[index]->move(new_x, new_y);
}

int Scheme::getIndexOfFigure(int id){
    for(int i = 0; i < size; i++){
        if(figures[i]->get_id() == id){
            return i;
        }
    }
    return -1;
}