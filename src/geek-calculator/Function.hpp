#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <iostream>
#include <string>
#include <mgl2/qt.h>
#include <QString>
#include <vector>

class Function {
public:

    Function(const QString& str_func);
    ~Function();
    float get_value();
    float integral(const float a, const float b);

    


private:
    QString m_function;
    float function_value;
    bool check_function();
    std::vector<float> linspace(const float a, const float b, const size_t n);
    

};


#endif
