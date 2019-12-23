%option noyywrap
%option noinput
%option nounput

%{
    #include <iostream>
    #include <cstdlib>
    #include <string>
    #include <fstream>
    #include "MatrixHelper.hpp"
    #include "parserMatrix.tab.hpp"
    
%}

%%

[0-9]+(\.[0-9]+)? {
    yylval.value = atof(yytext);
        return NUMBER;
}

trans {
    return TRANS;
}

inv {
    return INV;
}

norm {
    return NORM;
}

det {
    return DET;
}


[Aa] {
    return A;
}

[Bb] {
    return B;
}

[-+*/^()%!,] {
    return *yytext;
}


[ \t\n] {
    
}

. {
    std::cout << " greska u lekseru " << std::endl;
    exit(EXIT_FAILURE);

}
