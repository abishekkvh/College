%{
#include <stdio.h>
#include <ctype.h>
%}

word    [a-zA-Z]

%%

{word}+  { if(yyleng == 5) { yytext[0] = toupper(yytext[0]); printf("%s", yytext); } else { printf("%s", yytext); } }

.|\n    { ECHO; }

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
        yyin = fp;
    }

    yylex();
    printf("\n");
    return 0;
}