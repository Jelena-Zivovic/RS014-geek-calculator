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
    return SIN;
}

cos {
    return COS;
}

tg {
    return TG;
}

ctg {
    return CTG;
}

arcsin {
    return ASIN;
}

arccos {
    return ACOS;
}

arctg {
    return ATG;
}

arcctg {
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

[a-z] {
    return VARIABLE;
}

[-+*/^()%!] {
    return *yytext;
}


[ \t\n] ;

. {
    
}
