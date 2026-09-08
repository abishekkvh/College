%{
#include <stdio.h>
#include <stdlib.h>

extern FILE *yyin;
%}

datatype    "int"|"float"|"char"|"double"
id          [a-zA-Z_][a-zA-Z0-9_]*
dimension   \[[ \t]*[0-9]*[ \t]*\]
init_list   \{[^}]*\}

%%

{datatype}      { printf("DATA TYPE : %s\n", yytext); }

{id}            { printf("ARRAY NAME : %s\n", yytext); }

{dimension}     { printf("DIMENSION : %s\n", yytext); }

"="             { printf("OPERATOR : %s\n", yytext); }

{init_list}     { printf("INITIALIZER LIST: %s\n", yytext); }

";"             { printf("PUNCTUATION : %s\n", yytext); }

[ \t\n]+        ;

.               { /* Ignore other characters */ }

%%

int yywrap()
{
    return 1;
}

int main()
{
    yyin = fopen("array_input.txt", "r");

    if (yyin == NULL)
    {
        printf("File not found\n");
        return 1;
    }

    yylex();

    fclose(yyin);
    return 0;
}
