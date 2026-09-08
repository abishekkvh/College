%{
#include <stdio.h>
#include <stdlib.h>

extern FILE *yyin;
%}

%x UNARY

id      [a-zA-Z][a-zA-Z0-9_]*
digit   [0-9]+

%%

{id}        { printf("IDENTIFIER : %s\n", yytext); BEGIN 0; }

{digit}     { printf("NUMBER : %s\n", yytext); BEGIN 0; }

"+"|"*"|"/"|"="|"%" {
                printf("OPERATOR : %s\n", yytext);
                BEGIN UNARY;
            }

"-"         {
                printf("SUBTRACTION OPERATOR\n");
                BEGIN UNARY;
            }

"("         {
                printf("LEFT PARENTHESIS\n");
                BEGIN UNARY;
            }

")"         {
                printf("RIGHT PARENTHESIS\n");
                BEGIN 0;
            }

<UNARY>"-"  {
                printf("UNARY MINUS\n");
                BEGIN UNARY;
            }

<UNARY>{id} {
                printf("IDENTIFIER : %s\n", yytext);
                BEGIN 0;
            }

<UNARY>{digit} {
                printf("NUMBER : %s\n", yytext);
                BEGIN 0;
            }

<UNARY>"("  {
                printf("LEFT PARENTHESIS\n");
                BEGIN UNARY;
            }

<UNARY>[ \t\n]+ ;

[ \t\n]+ ;

.           {
                printf("UNKNOWN : %s\n", yytext);
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

    BEGIN UNARY;      /* Expression starts expecting an operand */

    yylex();

    fclose(yyin);
    return 0;
}