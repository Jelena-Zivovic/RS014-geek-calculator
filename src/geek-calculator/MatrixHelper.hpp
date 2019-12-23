#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include <eigen3/unsupported/Eigen/MatrixFunctions>
#include <eigen3/Eigen/LU>
#include <iostream>

class MatrixH
{
private:
    unsigned _n;
    unsigned _m;
    //Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> _matrix;
    Eigen::MatrixXd _matrix;

    friend std::ostream &operator<<(std::ostream &out, const MatrixH &m);

public:
    MatrixH();
    //Matrix(const QString text);
    MatrixH(unsigned n, unsigned m);
    Matrix(Eigen::MatrixHXd matrix);
    MatrixH(std::vector<std::vector<double>> &vec);
    Matrix(const MatrixH &m);
    ~Matrix() = default;

    unsigned rows() const;
    unsigned cols() const;

    MatrixH *operator+(const Matrix &m) const;
    MatrixH *operator-(const Matrix &m) const;
    MatrixH *operator*(const Matrix &m) const;
    MatrixH &operator=(const Matrix &m);
    MatrixH *inv() const;
    Matrix *transpose() const;

    MatrixH *operator*(double scalar) const;
    Matrix *operator/(double scalar) const;

    MatrixH *operator-() const;

    Matrix *pow(double power) const;
    MatrixH *normalized() const;

    double det() const;
    double norm() const;
};

std::ostream &operator<<(std::ostream &out, const Matrix &m);

#endif // MATRIX_HPP
