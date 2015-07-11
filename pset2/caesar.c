
/**
 * caesar.c
 *
 * Jonathan Sonnerup
 * Nooxet@gmail.com
 *
 * A program to encrypt a text string using Caesar cipher
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include <cs50.h>

char shift(char, int);

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <key>\n", argv[0]);
        return 1;
    }

    int key = atoi(argv[1]);

    /* get input from user */
    string text = GetString();
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        /* shift if char is alpha, else not */
        if (isalpha(text[i]))
        {
            text[i] = shift(text[i], key);
        }
    }

    printf("%s\n", text);
    return 0;
}

char shift(char chr, int key)
{
    if (isupper(chr))
    {
        return ((chr - 'A') + key) % 26 + 'A';
    }
    else
    {
        return ((chr - 'a') + key) % 26 + 'a';
    }
}
