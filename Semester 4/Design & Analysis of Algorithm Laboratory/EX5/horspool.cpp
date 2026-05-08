#include <iostream>
#include <string>
using namespace std;

#define MAX 256

void shiftTable(string pattern, int table[])
{
    int m = pattern.length();

    for(int i = 0; i < MAX; i++)
    {
        table[i] = m;
    }

    for(int j = 0; j < m - 1; j++)
    {
        table[(int)pattern[j]] = m - 1 - j;
    }
}

int horspool(string text, string pattern)
{
    int table[MAX];

    shiftTable(pattern, table);

    int n = text.length();
    int m = pattern.length();

    int i = m - 1;

    while(i < n)
    {
        int k = 0;

        while(k < m && pattern[m - 1 - k] == text[i - k])
        {
            k++;
        }

        if(k == m)
        {
            return i - m + 1;
        }
        else
        {
            i = i + table[(int)text[i]];
        }
    }

    return -1;
}

int main()
{
    string text, pattern;

    cout << "Enter text: ";
    getline(cin, text);

    cout << "Enter pattern: ";
    getline(cin, pattern);

    int pos = horspool(text, pattern);

    if(pos != -1)
    {
        cout << "Pattern found at position: " << pos;
    }
    else
    {
        cout << "Pattern not found";
    }

    return 0;
}