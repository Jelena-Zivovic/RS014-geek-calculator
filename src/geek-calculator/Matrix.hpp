#ifndef MATRICA_HPP
#define MATRICA_HPP

#include <vector>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include <eigen3/unsupported/Eigen/MatrixFunctions>
#include <iostream>
#include <QString>
#include <QStringList>
#include <QRegExp>

class Matrix{
private:
    unsigned _n;
    unsigned _m;
    //Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> _matrix;
    Eigen::MatrixXd _matrix;


    friend std::ostream& operator<<(std::ostream& out, const Matrix& m);

public:
    Matrix();
    //Matrix(const QString text);
    Matrix(unsigned n, unsigned m);
    Matrix(std::vector<std::vector<double>>& vec);
    Matrix(const Matrix& m);
    ~Matrix() = default;


    Matrix operator+(Matrix& m) const;
    Matrix operator-(Matrix& m) const;
    Matrix operator*(Matrix& m) const;
    Matrix operator/(Matrix& m) const;
    Matrix inv() const;
    Matrix transpose() const;

    Matrix operator*(double scalar) const;
    Matrix operator/(double scalar) const;

    Matrix pow(int power) const;
    Matrix normalized() const;

    static Eigen::MatrixXd parseText(QString, unsigned n, unsigned m);
    static bool check_matrix(QString text, unsigned n, unsigned m);
    double det() const;
    double norm() const;

};

std::ostream& operator<<(std::ostream& out, const Matrix& m);

#endif // MATRICA_HPP
