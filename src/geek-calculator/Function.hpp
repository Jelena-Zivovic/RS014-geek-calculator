#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <iostream>
#include <string>
#include <mgl2/qt.h>
#include <QString>
#include <vector>

class Function {
public:

    Function(const QString& str_func, const int number_of_variables=1);
    ~Function();
    double get_value();
    double oneVariableIntegral(const double a, const double b);
    double twoVariableIntegral(const double a1, const double b1, const double a2, const double b2);
    double firstDerivative(const double point);
    double secondDerivative(const double point);
    QString get_string_function() const;

    


private:
    QString m_function;
    double function_value;
    int m_number_of_variables;
    bool check_function();
    std::vector<double> linspace(const double a, const double b, const size_t n);

    

};



#endif
