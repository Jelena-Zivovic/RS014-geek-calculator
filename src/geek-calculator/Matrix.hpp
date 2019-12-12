#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>
#include <cstdlib>
#include <QString>

class Matrix{
private:
    std::vector<std::vector<double>> _m;
    QString _text;
public:
    Matrix() {}
    Matrix(QString text);
    Matrix(int m, int n);
    Matrix(Matrix& m);

    std::vector<double> operator [](int i) const;
    std::vector<double>& operator [](int i);

    Matrix* operator +(Matrix& m) const;
    Matrix* operator -(Matrix& m) const;
    Matrix* operator *(Matrix& m) const;
    Matrix* operator -() const;

    Matrix* transpose() const;
    Matrix* scalarMultiply(Matrix& m) const;

    void addRow(std::vector<double>& v);


};

#endif // MATRIX_HPP
