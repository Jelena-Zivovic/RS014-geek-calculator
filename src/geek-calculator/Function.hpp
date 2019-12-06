#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <iostream>
#include <string>
#include <mgl2/qt.h>

class Function {
public:

    Function(const std::string& str_func);
    ~Function();
    float get_value();
    std::string get_function_string() const;
    void draw_function(mglGraph *gr) const;
    


private:
    std::string m_function;
    float function_value;
    bool check_function();
    

};


#endif
