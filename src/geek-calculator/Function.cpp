#include "Function.hpp"
#include "Help_File.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <mgl2/qt.h>
#include "parser.tab.hpp"

//TODO lexer should read from string
bool indicator_calculating_value;
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
    indicator_calculating_value = false;
    Help_File file;

    file.write(m_function);

    yyin = file.get_FILE();
    float ignore_value;
    int return_value = yyparse(&ignore_value);

    return return_value == 0 ? true : false;
    
}

float Function::get_value()  {

    indicator_calculating_value = true;

    Help_File file;

    file.write(m_function);

    yyin = file.get_FILE();

    yyparse(&function_value);

    return function_value;

}


std::string Function::get_function_string() const {
    return m_function;
}



void Function::draw_function(mglGraph *gr) const {
   

}




















