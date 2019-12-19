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
    float get_value();
    float oneVariableIntegral(const float a, const float b);
    float twoVariableIntegral(const float a1, const float b1, const float a2, const float b2);
    QString get_string_function() const;

    


private:
    QString m_function;
    float function_value;
    bool check_function();
    std::vector<float> linspace(const float a, const float b, const size_t n);
    int m_number_of_variables;
    

};



#endif
