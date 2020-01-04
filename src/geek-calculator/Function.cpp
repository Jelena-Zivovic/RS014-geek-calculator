#include "Function.hpp"
#include <string>
#include <iostream>
#include <mgl2/qt.h>
#include "parser.tab.hpp"
#include <iterator>
#include <mgl2/mgl.h>
#include <mgl2/eval.h>
#include <algorithm>

//TODO lexer should read from string
bool indicator_calculating_value;
extern int yyparse(float *return_value);

void setInputString(const char *input);
void endLexicalScan(void);

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

    double ignore_value;

    setInputString(m_function.toUtf8().constData());

    int return_value = yyparse(&ignore_value);

    endLexicalScan();

    return return_value == 0 ? true : false;
    
}

double Function::get_value()  {

    indicator_calculating_value = true;

    setInputString(m_function.toUtf8().constData());

    yyparse(&function_value);

    endLexicalScan();

    return function_value;

}

QString Function::get_string_function() const {
    return m_function;
}

std::vector<double> Function::linspace(const double a, const double b, const size_t n) {
    double h = (b-a) / static_cast<double>(n-1);
    std::vector<double> xs(n);
    double val = a;
    auto first = std::begin(xs);
    auto last = std::end(xs);

    while (first != last) {
        *first = val;
        val += h;
        first++;
    }

    return xs;
}

double Function::oneVariableIntegral(const double a, const double b) {

   size_t n = 1001;

   std::vector<double> x = linspace(a, b, n);

   double h = (b - a) / static_cast<double>(n);

   std::vector<double> result(x.size());
   std::transform(x.begin(), x.end(), result.begin(), [this](double element) {
       mglFormula formula(m_function.toUtf8().constData());
       return formula.Calc(static_cast<mreal>(element));
   });

    double sumOddIndexElements = 0;
    double sumEvenIndexElements = 0;

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

double Function::twoVariableIntegral(const double a1, const double b1, const double a2, const double b2) {
    size_t n = 1001;

    std::vector<double> x = linspace(a1, b1, n);
    double hx = (b1 - a1) / static_cast<double>(n);

    std::vector<double> y = linspace(a2, b2, n);
    double hy = (b2 - a2) / static_cast<double>(n);

    size_t array_size = x.size();

    std::vector<std::vector<double> > matrix_f(array_size);

    for (size_t i = 0; i < array_size; i++) {
        matrix_f[i].resize(array_size);
    }

    mglFormula formula(m_function.toUtf8().constData());

    for (size_t i = 0; i < array_size; i++) {
        for (size_t j = 0; j < array_size; j++) {
            matrix_f[i][j] = formula.Calc(static_cast<mreal>(x[i]), static_cast<mreal>(y[j]));
        }
    }

    std::vector<double> ax(array_size);

    for (size_t i = 0; i < array_size; i++) {
        double sumOddIndexElements = 0;
        double sumEvenIndexElements = 0;

        for (size_t j = 0; j < array_size; j++) {
            if (j % 2 != 0) {
                sumOddIndexElements += matrix_f[i][j];
            }
            else {
                sumEvenIndexElements += matrix_f[i][j];
            }
        }

        ax[i] = (hy/3) * (matrix_f[i][0] + matrix_f[i][array_size-1] + 4*sumOddIndexElements + 2*sumEvenIndexElements);

    }

    double sumOddIndexElements = 0;
    double sumEvenIndexElements = 0;

    for (size_t i = 0; i < array_size; i++) {
        if (i % 2 != 0) {
            sumOddIndexElements += ax[i];
        }
        else {
            sumEvenIndexElements += ax[i];
        }
    }

    double result = (hx/3) * (ax[0] + ax[array_size-1] + 4*sumOddIndexElements + 2*sumEvenIndexElements);



    return result;
}

double Function::firstDerivative(const double point) {

    mglFormula formula(m_function.toUtf8().constData());

    double h = 0.01;

    double result = (formula.Calc(point+h) - formula.Calc(point-h))/(2*h);

    return result;

}
double Function::secondDerivative(const double point) {
    mglFormula formula(m_function.toUtf8().constData());

    double h = 0.01;

    double result = (formula.Calc(point+h) - 2*formula.Calc(point) + formula.Calc(point-h))/(h*h);

    return result;
}




















