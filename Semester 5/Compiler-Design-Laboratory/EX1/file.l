%{
#include <stdio.h>
#include <stdlib.h>

int letter_count = 0;
int word_count = 0;
int line_count = 0;
%}

%%
\n          { line_count++; letter_count++; }
[ \t]       { letter_count += yyleng; }
[^ \t\n]+   { word_count++; letter_count += yyleng; }
%%

int main(int argc, char *argv[]) 
{
    if (argc > 1) 
    {
        FILE *file = fopen(argv[1], "r");
        if (!file) 
        {
            fprintf(stderr, "Error: Could not open file %s\n", argv[1]);
            return 1;
        }
        yyin = file; 
    } 
    else 
    {
        printf("No file provided. Enter text manually (Press Ctrl+D to finish):\n");
    }

    yylex(); 

    printf("\n--- Results ---\n");
    printf("Total Lines      : %d\n", line_count);
    printf("Total Words      : %d\n", word_count);
    printf("Total Characters : %d\n", letter_count);

    return 0;
}

int yywrap() 
{
    return 1;
}
