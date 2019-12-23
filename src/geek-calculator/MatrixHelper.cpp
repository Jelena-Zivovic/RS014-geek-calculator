#include "MatrixHelper.hpp"

MatrixH::MatrixH()
{
    _n = 0;
    _m = 0;
    _matrix.resize(0, 0);
}

MatrixH::MatrixH(unsigned n, unsigned m) : _n(n), _m(m)
{
    _matrix.resize(n, m);
}
MatrixH::MatrixH(Eigen::MatrixXd matrix)
{
    _n = static_cast<unsigned>(matrix.rows());
    _m = static_cast<unsigned>(matrix.cols());
    _matrix.resize(_n, _m);
    _matrix = matrix;
}

MatrixH::MatrixH(const MatrixH &m) : _n(m._n), _m(m._m)
{
    _matrix.resize(m._n, m._m);
    _matrix = m._matrix;
}
MatrixH::MatrixH(std::vector<std::vector<double>> &vec)
{
    unsigned n = static_cast<unsigned>(vec.size());
    unsigned m = static_cast<unsigned>(vec[0].size());
    _n = n;
    _m = m;
    _matrix.resize(n, m);

    for (unsigned i = 0; i < _n; i++)
    {
        for (unsigned j = 0; j < _m; j++)
            _matrix(i, j) = vec[i][j];
    }
}
unsigned MatrixH::rows() const
{
    return _n;
}
unsigned MatrixH::cols() const
{
    return _m;
}

MatrixH *MatrixH::operator+(const MatrixH &m) const
{
    if (_n != m._n || _m != m._m)
    {
        return nullptr;
    }
    MatrixH *newMatrix = new MatrixH(_n, _m);
    newMatrix->_matrix = _matrix + m._matrix;
    return newMatrix;
}
MatrixH *MatrixH::operator-(const MatrixH &m) const
{
    if (_n != m._n || _m != m._m)
    {
        return nullptr;
    }
    MatrixH *newMatrix = new MatrixH(_n, _m);
    newMatrix->_matrix = _matrix - m._matrix;
    return newMatrix;
}
MatrixH *MatrixH::operator-() const
{
    MatrixH *newMatrix = new MatrixH(_n, _m);
    newMatrix->_matrix = -_matrix;
    return newMatrix;
}
MatrixH *MatrixH::operator*(const MatrixH &m) const
{
    if (_m != m._n)
    {
        return nullptr;
    }
    MatrixH *newMatrix = new MatrixH(_n, m._m);
    newMatrix->_matrix = _matrix * m._matrix;
    return newMatrix;
}
MatrixH &MatrixH::operator=(const MatrixH &m)
{
    _matrix = m._matrix;
    _n = m._n;
    _m = m._m;
    return *this;
}
MatrixH *MatrixH::inv() const
{
    if (this->det() == 0)
    {
        return nullptr;
    }
    Matrix *newMatrix = new MatrixH(_n, _m);
    newMatrix->_matrix = _matrix.inverse();
    return newMatrix;
}
MatrixH *MatrixH::transpose() const
{
    Matrix *newMatrix = new MatrixH(_m, _n);
    newMatrix->_matrix = _matrix.transpose();
    return newMatrix;
}
MatrixH *MatrixH::operator*(double scalar) const
{
    Matrix *newMatrix = new MatrixH(_n, _m);
    newMatrix->_matrix = _matrix * scalar;
    return newMatrix;
}

MatrixH *MatrixH::operator/(double scalar) const
{
    Matrix *newMatrix = new MatrixH(_n, _m);
    newMatrix->_matrix = _matrix / scalar;
    return newMatrix;
}
MatrixH *MatrixH::pow(double power) const
{
    Matrix *newMatrix = new MatrixH(_n, _m);
    newMatrix->_matrix = _matrix.pow(power);
    return newMatrix;
}

Matrix *Matrix::normalized() const
{
    Matrix *newMatrix = new MatrixH(_n, _m);
    newMatrix->_matrix = _matrix.normalized();
    return newMatrix;
}
double MatrixH::det() const
{
    return _matrix.determinant();
}
double MatrixH::norm() const
{
    return _matrix.norm();
}

std::ostream &operator<<(std::ostream &out, const MatrixH &m)
{
    return out << m._matrix << std::endl;
}
