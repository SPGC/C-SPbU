#include "matrix.hpp"

Matrix::Matrix(std::size_t r, std::size_t c) {
  _rows = r;
  _cols = c;
  _data = new int* [r];
  for(std::size_t i = 0; i < r; i++)
    _data[i] = new int[c]();
}

Matrix::~Matrix(){
    if (_data == 0)
        return;
    for (std::size_t i = 0; i < _rows; i++){
        delete[] _data[i];
    }
        delete[] _data;
}

std::size_t Matrix::get_rows() const { 
    return _rows; 
}
std::size_t Matrix::get_cols() const { 
    return _cols; 
}

void Matrix::set(std::size_t i, std::size_t j, int val) {
  _data[i][j] = val;
}

int Matrix::get(std::size_t i, std::size_t j) const{
  return _data[i][j];
}

bool Matrix::operator==(const Matrix& that) const{
    if (_rows != that._rows || _cols != that._cols){
        return false;
    }
    for (std::size_t i = 0; i < _rows; i++){
        for (std::size_t j = 0; j < _cols; j++){
            if(_data[i][j] != that._data[i][j]){
                return false;
            }
        }    
    }   
    return true;
}

bool Matrix::operator!=(const Matrix& that) const{
  return !(operator==(that));
}