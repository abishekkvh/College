%{
#include <stdio.h>
%}

space [ \t]

%%

{space}+      { printf(" "); }

\n          { printf("\n"); }

.           { ECHO; }

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
            printf("Cannot open file\n");
            return 1;
        }

        yyin = fp;
    }

    yylex();
    printf("\n");
    return 0;
}