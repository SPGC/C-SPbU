#include "my_vector.hpp"

#include <cstdlib>
#include <stdexcept>    
#include <cstring>

MyVector::MyVector(){
    _capacity = 2;
    _size = 0;
    _data = (int*)malloc(_capacity * sizeof(int));
    if(_data == NULL){
       throw std::runtime_error("Memmory allocation failed");
    }
}

MyVector::MyVector(size_t init_capacity){
    _size = 0;
    _capacity = init_capacity;
    _data = (int*)malloc(_capacity * sizeof(int));
    if(_data == NULL){
       throw std::runtime_error("Memmory allocation failed");
    }
}

MyVector::MyVector(const MyVector& vector){
    _size = vector._size;
    _capacity = vector._capacity;
    _data = (int*)malloc(_capacity * sizeof(int));
    if(_data == NULL){
       throw std::runtime_error("Memmory allocation failed");
    }
    memcpy(_data, vector._data, sizeof(int)*_size);
}

MyVector& MyVector::operator=(const MyVector& vector){
    int *buffer = (int*)realloc(_data, vector._capacity * sizeof(int));
    if(buffer == NULL){
       throw std::runtime_error("Memmory allocation failed. Data hasn't been changed");
    }
    _data = buffer;
    _size = vector._size;
    _capacity = vector._capacity;
    memcpy(_data, vector._data, sizeof(int)*_size);
    return *this;
}

 MyVector::~MyVector(){
     free(_data);
 }

void  MyVector::set(size_t i, int value){
    if(i >=_size){
        throw std::runtime_error("Array index out of bound");
    }
    _data[i] = value;
}

int MyVector::get(size_t i){
    if(i >=_size){
        throw std::runtime_error("Array index out of bound");
    }
     return _data[i];
}

size_t MyVector::size(){
     return _size;
}

size_t MyVector::capacity(){
    return _capacity;
}

void MyVector::push_back(int value){
    resize(_size + 1);
    _data[_size - 1] = value;
}

void MyVector::insert(size_t index, int value){
    if(index >_size){
        throw std::runtime_error("Array index out of bound");
    }
    resize(_size + 1);
    int bufferPrev = value;
    int bufferCur;
    for (size_t i = index; i < _size; i++){
        bufferCur = _data[i];
        _data[i] = bufferPrev;
        bufferPrev = bufferCur;
    }
}

void MyVector::erase(size_t index){
    if(index >= _size){
        throw std::runtime_error("Array index out of bound");
    }
    for (size_t i = index; i<_size - 1; i++){
        _data[i] = _data[i + 1];
    }
    _size--;
}

void MyVector::reserve(size_t new_capacity){
    if(new_capacity > _capacity){
        _capacity = new_capacity;
        int *buffer = (int *)realloc(_data, _capacity * sizeof(int));
        if(buffer == NULL){
            free(_data);
            throw std::runtime_error("Memmory allocation failed");
        } else {
            _data = buffer;
        }
    }
}

void MyVector::resize(size_t new_size){
    if(new_size > _capacity){
        reserve(std::max(new_size, _capacity * 2));
    }
    for (size_t i = _size; i < new_size; i++){
        _data[i] = 0;
    }
    _size = new_size;
}