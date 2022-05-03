#ifndef MATRIX
#define MATRIX

#include <fstream>


class Matrix {
public:
    Matrix() noexcept;
    Matrix(int rows, int collumns);

    Matrix(const Matrix &matrix);

    Matrix &operator=(const Matrix &matrix);

    int get(int i, int j) const;

    int *operator[](int row) noexcept;
    const int *operator[](int row) const noexcept;

    Matrix &operator+=(const Matrix &matrix);
    Matrix &operator*=(const Matrix &matrix);

    friend std::ostream &operator<<(std::ostream &out, const Matrix &matrix);
    friend std::ifstream &operator>>(std::ifstream &in, Matrix &matrix);

    ~Matrix();

private:
    static int **arrayConstructor(int r, int c);
    void dataDestructor();

    void checkIndixesForAccess(int i, int j) const;
    void checkIndixesForSum(const Matrix &matrix) const;
    void checkIndixesForMultiply(const Matrix &matrix) const;

    int rows = 0;
    int collumns = 0;
    int **data = nullptr;
};

class MatrixException : public std::exception {
public:
    MatrixException(std::string message);

    const char *what() const noexcept override;

private:
    std::string message;
};

#endif 