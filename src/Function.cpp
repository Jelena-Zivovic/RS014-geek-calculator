#include "Function.hpp"
#include "Help_File.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include "parser.tab.hpp"

extern FILE *yyin;
extern int yyparse(float *return_value);



Function::Function(const std::string& str_func)
    : m_function(str_func) {
        if (!check_function()) {
            throw "Function is not valid";
        }
    }

Function::~Function() {

}
    

bool Function::check_function()  {
    Help_File fajl;

    fajl.write(m_function);

    yyin = fajl.get_FILE();

    int return_value = yyparse(&function_value);

    return return_value == 0 ? true : false;
    
}

float Function::get_function_value() const {
    return function_value;

}























