#include "Matrix.hpp"


int **Matrix::arrayConstructor(int rows, int collumns) {
    if (rows == 0 || collumns == 0){
        return nullptr;
    }
    int **result = (int **) malloc(rows * sizeof(int*));
    int *buffer;
    for(int i = 0; i < rows; i++){
        buffer = (int *)malloc(collumns * sizeof(int));
        std::fill_n(buffer, collumns, 0);
        result[i] = buffer;
    }
    return result;
}

void Matrix::dataDestructor(){
    for(int i = 0; i < rows; i++){
        free(data[i]);
    }
    free(data);
}

Matrix::Matrix(int rows, int collumns){
    this->rows = rows;
    this->collumns = collumns;
    data = arrayConstructor(rows, collumns);
}

Matrix::Matrix() noexcept{
    this->rows = 0;
    this->collumns = 0;
    data = nullptr;
}

Matrix::Matrix(const Matrix &matrix) {
    *this = matrix;
}

Matrix::~Matrix() {
    dataDestructor();
}

Matrix &Matrix::operator=(const Matrix &matrix) {
    if (this == &matrix)
        return *this;

    if (rows != matrix.rows || collumns != matrix.collumns) {
        int **new_data = arrayConstructor(matrix.rows, matrix.collumns);
        dataDestructor();
        data = new_data;
    }
    for(int i = 0; i< matrix.rows; i++){
        for (int j = 0; j < matrix.collumns; j++){
            data[i][j] = matrix[i][j];
        }
    }
    rows = matrix.rows;
    collumns = matrix.collumns;

    return *this;
}

int Matrix::get(int i, int j) const {
    checkIndixesForAccess(i, j);
    return data[i][j];
}

int *Matrix::operator[](int row) noexcept {
    return data[row];
}

const int *Matrix::operator[](int row) const noexcept {
    return data[row];
}

Matrix &Matrix::operator+=(const Matrix &other) {
    checkIndixesForSum(other);
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < collumns; ++j)
            data[i][j] += other[i][j];
    return *this;
}

Matrix &Matrix::operator*=(const Matrix &matrix) {
    checkIndixesForMultiply(matrix);
    Matrix buffer(rows, matrix.collumns);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < matrix.collumns; j++)
            for (int k = 0; k < collumns; k++)
                buffer[i][j] += data[i][k] * matrix[k][j];
    return *this = buffer;
}

std::ostream &operator<<(std::ostream &out, const Matrix &matrix) {
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.collumns; j++) {
            out << matrix[i][j];
            if (j != matrix.collumns - 1)
                out << " ";
        }
        out << "\n";
    }
    return out;
}

std::ifstream &operator>>(std::ifstream &in, Matrix &matrix) {
    if (!in.is_open())
        throw MatrixException("LOAD: unable to open file.");
    int rows, collumns;
    if (!(in >> rows) || !(in >> collumns))
        throw MatrixException("LOAD: invalid file format.");
    Matrix res(rows, collumns);
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < collumns; j++){
            if (!(in >> res[i][j])){
                throw MatrixException("LOAD: invalid file format.");
            }
        }
    }
    matrix = res;
    return in;
}

void Matrix::checkIndixesForAccess(int i, int j) const {
    if (i < 0 || j < 0 || i >= rows || j >= collumns){
        throw MatrixException("ACCESS: bad index.");
    }
}

void Matrix::checkIndixesForSum(const Matrix &matrix) const {
    if (rows != matrix.rows || collumns != matrix.collumns){
        throw MatrixException("ADD: dimensions do not match.");
    }
}

void Matrix::checkIndixesForMultiply(const Matrix &matrix) const {
    if (collumns != matrix.rows){
        throw MatrixException("MUL: #arg1.columns != #arg2.rows.");
    }
}

MatrixException::MatrixException(std::string message){
    this->message = std::move(message);
}

const char *MatrixException::what() const noexcept {
    return message.c_str();
}