%{
#include <stdio.h>
#include <stdlib.h>

extern FILE *yyin;
%}

id      [a-zA-Z][a-zA-Z0-9_]*
digit   [0-9]+

%%

{id}            { printf("IDENTIFIER : %s\n", yytext); }

"+="|"-="|"*="|"/="|"%=" {
                    printf("COMPOUND OP : %s\n", yytext);
                }

"="             {
                    printf("SIMPLE OP : %s\n", yytext);
                }

";"             {
                    printf("PUNCTUATION : %s\n", yytext);
                }

{digit}         {
                    printf("INT CONSTANT : %s\n", yytext);
                }

[ \t\n]+        ;

.               {
                    /* Ignore unknown characters */
                }

%%

int yywrap()
{
    return 1;
}

int main()
{
    yyin = fopen("input.txt", "r");

    if (yyin == NULL)
    {
        printf("File not found\n");
        return 1;
    }

    yylex();

    fclose(yyin);
    return 0;
}
