%option noyywrap
%option noinput
%option nounput

%{
    #include <iostream>
    #include <cstdlib>
    #include <string>
    #include <fstream>
    
    #include "parser.tab.hpp"
    
%}

%%

[0-9]+(\.[0-9]+)? {
    yylval.value = atof(yytext);
        return NUMBER;
}

sin {
    return SINUS;
}

[()] {
    return *yytext;
}

[\n \t] {

}

. {
   
}
