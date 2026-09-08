%{
#include <stdio.h>
%}

%x COMMENT

%%

"/*"            { BEGIN(COMMENT); }

<COMMENT>"*/"   { 
                    printf("Valid Comment\n"); 
                    BEGIN(INITIAL); 
                }

<COMMENT><<EOF>> { 
                    printf("Invalid/Incomplete Comment\n"); 
                    BEGIN(INITIAL); 
                    return 0; 
                }

<COMMENT>.|\n   { /* Ignore all characters inside the comment */ }

.|\n            { /* Ignore all characters outside the comment */ }

%%

int yywrap() {
    return 1;
}

int main(int argc, char* argv[]) 
{
    FILE *fp = fopen(argv[1], "r");

    if(fp == NULL)
    {
        printf("File not found\n");
        return 1;
    }

    yyin = fp;
    yylex();

    fclose(fp);

    return 0;
}
