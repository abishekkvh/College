%{
#include<stdio.h>
#include<stdlib.h>
%}

digits [0-9]
float [0-9]+\.[0-9]+

%%

{float} {printf("Floating-Numbers : %.2f\n", atof(yytext)+0.5);}

{digits}+ {printf("Integers : %d\n", atoi(yytext)+1);}

. ;

\n ;

%%

int yywrap()
{
    return 1;
}

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        FILE *fp = fopen(argv[1], "r");

        if (fp == NULL)
        {
            printf("Cannot open file.\n");
            return 1;
        }

        yyin = fp;
        yylex();
    }

    return 0;
}