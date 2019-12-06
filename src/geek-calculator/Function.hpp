#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <iostream>
#include <string>
#include <mgl2/qt.h>
#include <QString>

class Function {
public:

    Function(const QString& str_func);
    ~Function();
    float get_value();


    


private:
    QString m_function;
    float function_value;
    bool check_function();
    

};


#endif
