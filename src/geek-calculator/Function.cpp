#include "Function.hpp"
#include "Help_File.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <mgl2/qt.h>
#include "parser.tab.hpp"
#include <iterator>
#include <mgl2/mgl.h>
#include <mgl2/eval.h>
#include <algorithm>

//TODO lexer should read from string
 bool indicator_calculating_value;
extern FILE *yyin;
extern int yyparse(float *return_value);



Function::Function(const QString& str_func, const int number_of_variables)
    : m_function(str_func), m_number_of_variables(number_of_variables) {
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

QString Function::get_string_function() const {
    return m_function;
}

std::vector<float> Function::linspace(const float a, const float b, const size_t n) {
    float h = (b-a) / static_cast<float>(n-1);
    std::vector<float> xs(n);
    float val = a;
    auto first = std::begin(xs);
    auto last = std::end(xs);

    while (first != last) {
        *first = val;
        val += h;
        first++;
    }



    return xs;
}



float Function::oneVariableIntegral(const float a, const float b) {

   size_t n = 1001;

   std::vector<float> x = linspace(a, b, n);

   float h = (b - a) / static_cast<float>(n);

   std::vector<float> result(x.size());
   std::transform(x.begin(), x.end(), result.begin(), [this](float element) {
       mglFormula formula(m_function.toUtf8().constData());
       return formula.Calc(static_cast<mreal>(element));
   });

    float sumOddIndexElements = 0;
    float sumEvenIndexElements = 0;

    for (size_t i = 0; i < x.size(); i++) {
        if (i % 2 != 0) {
            sumOddIndexElements += result[i];
        }
        else {
            sumEvenIndexElements += result[i];
        }
    }

    return (h/3) * (result[0] + result[x.size()-1] + 4*sumOddIndexElements + 2*sumEvenIndexElements);


}





















