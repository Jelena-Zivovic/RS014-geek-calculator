#include "Matrix.hpp"

Matrix::Matrix(){
    _n = 2;
    _m = 2;
    _matrix.resize(2,2);
}

Matrix::Matrix(unsigned n, unsigned m) : _n(n), _m(m){
    _matrix.resize(n,m);
}

Matrix::Matrix(const Matrix& m) : _n(m._n), _m(m._m){
    _matrix.resize(m._n, m._m);
    //_matrix=Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>(m._matrix);
    _matrix = m._matrix;
}
Matrix::Matrix(std::vector<std::vector<double>>& vec){
    unsigned n = static_cast<unsigned>(vec.size());
    unsigned m = static_cast<unsigned>(vec[0].size());
    _n = n;
    _m = m;
    _matrix.resize(n,m);

    for(unsigned i=0; i<_n; i++){
        for(unsigned j=0; j<_m; j++)
            _matrix(i,j) = vec[i][j];
    }
}

Matrix Matrix::operator+(Matrix& m) const{
    Matrix newMatrix(_n,_m);
    newMatrix._matrix = _matrix+m._matrix;
    return newMatrix;
}
Matrix Matrix::operator-(Matrix& m) const{
    Matrix newMatrix(_n,_m);
    newMatrix._matrix = _matrix-m._matrix;
    return newMatrix;
}
Matrix Matrix::operator*(Matrix& m) const{
    Matrix newMatrix(_n,_m);
    newMatrix._matrix = _matrix*m._matrix;
    return newMatrix;
}
Matrix Matrix::operator/(Matrix& m) const{
    Matrix newMatrix(m._m, _m);
    newMatrix._matrix = m._matrix.inverse()*_matrix;
    return newMatrix;
}
Matrix Matrix::inv() const{
    Matrix newMatrix(_n,_m);
    newMatrix._matrix = _matrix.inverse();
    return newMatrix;
}
Matrix Matrix::transpose() const{
    Matrix newMatrix(_m, _n);
    newMatrix._matrix = _matrix.transpose();
    return  newMatrix;

}
Matrix Matrix::operator*(double scalar) const{
    Matrix newMatrix(_n,_m);
    newMatrix._matrix = _matrix*scalar;
    return  newMatrix;
}

Matrix Matrix::operator/(double scalar) const{
    Matrix newMatrix(_n,_m);
    newMatrix._matrix = _matrix/scalar;
    return  newMatrix;
}
Matrix Matrix::pow(int power) const{
    Matrix newMatrix(_n,_m);
    _matrix.MatrixBase::pow(power);
    return newMatrix;
}

Matrix Matrix::normalized() const{
     Matrix newMatrix(_n,_m);
     newMatrix._matrix = _matrix.normalized();
     return newMatrix;
}
double Matrix::det() const{
    return _matrix.determinant();
}
double Matrix::norm() const{
    return _matrix.norm();
}
bool Matrix::check_matrix(QString text, unsigned n, unsigned m){
    QStringList list = text.trimmed().split(QRegExp("\\s+|\\n+"));
    bool ok;
    int k=0;
    if(list.size() != static_cast<int>(n*m)){
        return false;
    }
    for(unsigned i=0; i<n; i++){
        for(unsigned j=0; j<m; j++){
            list[k].toDouble(&ok);
            if(ok==false){
                return false;
            }
            k++;
        }
    }

    return true;
}
Eigen::MatrixXd Matrix::parseText(QString text, unsigned n, unsigned m){
    QStringList list = text.trimmed().split(QRegExp("\\s+|\\n+"));
    int k=0;
    Eigen::MatrixXd matrix;
    matrix.resize(n,m);
    for(unsigned i=0; i<n; i++){
        for(unsigned j=0; j<m; j++){
            matrix(i,j) = list[k].toDouble();
            k++;
        }
    }

    return matrix;
}
