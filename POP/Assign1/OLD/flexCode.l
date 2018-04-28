%{
    #include "y.tab.h"
    extern yy_bp, yy_cp;
    void setBuff(startOfWhile){
        yy_c_buf_p = startOfWhile;
    }
%}

%%
[ \t]           ;
return              { return ret;}
if                  { return IF; }
while               { yylval.start=yytext; return WHILE; }
[+-]?[1-9][0-9]*  { yylval.num= atoi(yytext); return number; }
[a-z]      	      { yylval.id=yytext[0]; return identifier; }
[\+\-\*\/\[\]\n\=;\<\>] { return yytext[0];};
.                 printf("Unknown Symbol %c at line %d", *yytext, yylineno);
%%
int yywrap(){
    return 0;
}
void yyerror(int error){}
/*
[; [= x 5] [; while [ < x 10 ] [= x [+ x 2]] [= x [* x 2]] ] [return x] ]
*/
