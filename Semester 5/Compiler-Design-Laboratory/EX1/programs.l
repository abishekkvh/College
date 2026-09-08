%{
#include <stdio.h>
%}


letter       [a-zA-Z_][a-zA-Z0-9_]*
float        [0-9]+\.[0-9]+
digit        [0-9]


keywords     (auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|inline|int|long|register|restrict|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while|_Bool|_Complex|_Imaginary)


operators    (\+\+|--|\+=|-=|\*=|\/=|%=|&=|\|=|\^=|<<=|>>=|==|!=|>=|<=|&&|\|\||<<|>>|->|\+|-|\*|\/|%|=|>|<|!|&|\||\^|~|\?|:|\.)


punctuations [;,(){}\[\]]

%%

{keywords}                { printf("<kw,%s> ", yytext); }

{letter}                  { printf("<id,%s> ", yytext); }

{float}                   { printf("%sf ", yytext); }

{digit}+                  { printf("%si ", yytext); }

{operators}               { printf("<op,%s> ", yytext); }

{punctuations}            { printf("%s ", yytext); }

[ \t\n]+                  ;      

.                         { printf("%s ", yytext); }

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
