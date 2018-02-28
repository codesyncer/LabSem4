%{
#include <stdio.h>
#include <string.h>
#define zero 0
int symbols[26];
int getVal(char symbol){
    return symbols[symbol-'a'];
}
void setVal(char symbol, int val){
    symbols[symbol-'a']= val;
}
%}

%union { int num; char id; char* start; }
%start line
%token <num> number
%token <id> identifier
%token <num> ret
%token <num> IF
%token <start> WHILE
%type <num> term
%type <num> exp
%type <num> exps
%%
line :
    exp '\n' {printf("%d\n", $1); exit(0);}
exps :
    exp exps {$$ = $2;}|
    exp {;};
exp :
    term {$$ = $1;} |
    '[' ';' exp exps ']' {$$ = $4;}|
    IF exp '[' '=' identifier exp ']' { if($2) { $$ = $6; setVal($5, $6);};} |
    '[' '=' identifier exp ']' { $$ = $4; setVal($3, $4);} |
    '[' '+' exp exp ']' {$$ = $3+$4;} |
    '[' '-' exp exp ']' {$$ = $3-$4;} |
    '[' '*' exp exp ']' {$$ = $3*$4;} |
    '[' '/' exp exp ']' {$$ = $3/$4;} |
    '[' '<' exp exp ']' {$$ = $3<$4;} |
    '[' '>' exp exp ']' {$$ = $3>$4;} |
    '[' ret term ']' { $$ = $3; };
term :
    number {$$ = $1;}    |
    identifier {$$ = getVal($1);};
%%
int main(){
    memset(symbols, 0, 26*sizeof(int));
    return yyparse();
}
