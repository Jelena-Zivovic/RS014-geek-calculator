#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <iostream>
#include <string>

class Function {
public:

    Function(const std::string& str_func);
    ~Function();
    float get_value();
    


private:
    std::string m_function;
    float function_value;
    bool check_function();

};


#endif
