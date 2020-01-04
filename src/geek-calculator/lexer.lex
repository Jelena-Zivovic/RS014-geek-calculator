%option noyywrap
%option noinput
%option nounput

%{
    #include <iostream>
    #include <cstdlib>
    #include <string>
    #include <fstream>
    #include <math.h>
    
    #include "parser.tab.hpp"
    
%}

%%

[0-9]+(\,[0-9]+)? {
    yylval.value = atof(yytext);
        return NUMBER;
}



sin {
    return SIN;
}

cos {
    return COS;
}

tan {
    return TG;
}

tg {
    return TG;
}

ctan {
    return CTG;
}

ctg {
    return CTG;
}

asin {
    return ASIN;
}

acos {
    return ACOS;
}

atan {
    return ATG;
}

actan {
    return ACTG;
}

ln {
    return LN;
}

log {
    return LOG;
}

exp {
    return EXP;
}

sqrt {
    return SQRT;
}

abs {
    return ABS;
}

mod {
    return MOD;
}

pi {
    yylval.value = M_PI;
    return NUMBER;
}

e {
    yylval.value = M_E;
    return NUMBER;
}

[a-z] {
    return VARIABLE;
}

[-+*/^()%!,] {
    return *yytext;
}


[ \t\n] ;

. {
    
}

%%

void setInputString(const char *input) {
    yy_scan_string(input);
}

void endLexicalScan(void) {
    yy_delete_buffer(YY_CURRENT_BUFFER);
}
