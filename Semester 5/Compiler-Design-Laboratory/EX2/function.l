%{
#include <stdio.h>
#include <stdlib.h>

extern FILE *yyin;
%}

id      [a-zA-Z_][a-zA-Z0-9_]*

%%

{id}/"("        { printf("FUNCTION CALL (right context '(' ahead) : %s\n", yytext); }

{id}            { printf("IDENTIFIER : %s\n", yytext); }

"("|")"|";"     { printf("PUNCTUATION : %s\n", yytext); }

[ \t\n]+        ;

.               { /* Ignore unknown characters */ }

%%

int yywrap()
{
    return 1;
}

int main()
{
    yyin = fopen("func_input.txt", "r");

    if (yyin == NULL)
    {
        printf("File not found\n");
        return 1;
    }

    yylex();

    fclose(yyin);
    return 0;
}
